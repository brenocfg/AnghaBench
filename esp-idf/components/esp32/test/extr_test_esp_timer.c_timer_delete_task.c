#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  delete_done; int /*<<< orphan*/  timer; int /*<<< orphan*/  delete_start; } ;
typedef  TYPE_1__ timer_delete_test_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_timer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_delete_task(void* arg)
{
    timer_delete_test_args_t* args = (timer_delete_test_args_t*) arg;
    xSemaphoreTake(args->delete_start, portMAX_DELAY);
    printf("Deleting the timer\n");
    esp_timer_delete(args->timer);
    printf("Timer deleted\n");
    xSemaphoreGive(args->delete_done);
    vTaskDelete(NULL);
}