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
 int /*<<< orphan*/  eNoAction ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ xTaskNotify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xTaskNotifyWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blink_task2(void *pvParameter)
{
    TaskHandle_t task = (TaskHandle_t)pvParameter;

    while(1) {
        if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) != pdPASS) {
            printf("Failed to wait for main task!\n");
            return;
        }
        void *a = malloc(65);
        printf("Alloced 65 bytes @ %p\n", a);
        void *b = malloc(97);
        printf("Alloced 97 bytes @ %p\n", b);
        free(a);
        printf("Freed @ %p\n", a);
        b = malloc(11);
        printf("Alloced 11 bytes @ %p\n", b);
        b = malloc(24);
        printf("Alloced 24 bytes @ %p\n", b);
        free(b);
        printf("Freed @ %p\n", b);
        if (xTaskNotify(task, 0, eNoAction) != pdPASS) {
            printf("Failed to notify main task!\n");
            return;
        }
    }
}