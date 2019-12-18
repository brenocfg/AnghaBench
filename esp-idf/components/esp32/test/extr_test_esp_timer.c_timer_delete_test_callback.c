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
struct TYPE_2__ {int /*<<< orphan*/  test_done; int /*<<< orphan*/  delete_done; int /*<<< orphan*/  delete_start; } ;
typedef  TYPE_1__ timer_delete_test_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_delete_test_callback(void* arg)
{
    timer_delete_test_args_t* args = (timer_delete_test_args_t*) arg;
    printf("Timer callback called\n");
    xSemaphoreGive(args->delete_start);
    xSemaphoreTake(args->delete_done, portMAX_DELAY);
    printf("Callback complete\n");
    xSemaphoreGive(args->test_done);
}