#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HEAP_TRACE_ALL ; 
 int /*<<< orphan*/  blink_task2 ; 
 int /*<<< orphan*/  eNoAction ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ heap_trace_init_tohost () ; 
 int /*<<< orphan*/  heap_trace_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_trace_stop () ; 
 void* malloc (int) ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 
 scalar_t__ xTaskNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xTaskNotifyWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blink_task(void *pvParameter)
{
    TaskHandle_t task = 0;

    if(heap_trace_init_tohost() != ESP_OK) {
        printf("Failed to init heap trace!\n");
        return;
    }
    xTaskCreatePinnedToCore(&blink_task2, "blink_task2", 2048, xTaskGetCurrentTaskHandle(), 5, &task, 1);

    while(1) {
        heap_trace_start(HEAP_TRACE_ALL);
        if (xTaskNotify(task, 0, eNoAction) != pdPASS) {
            printf("Failed to notify slave task!\n");
            return;
        }
        void *a = malloc(64);
        printf("Alloced 64 bytes @ %p\n", a);
        void *b = malloc(96);
        printf("Alloced 96 bytes @ %p\n", b);
        free(a);
        printf("Freed @ %p\n", a);
        b = malloc(10);
        printf("Alloced 10 bytes @ %p\n", b);
        b = malloc(23);
        printf("Alloced 23 bytes @ %p\n", b);
        free(b);
        printf("Freed @ %p\n", b);
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) != pdPASS) {
            printf("Failed to wait for slave task!\n");
            return;
        }
        heap_trace_stop();
    }
}