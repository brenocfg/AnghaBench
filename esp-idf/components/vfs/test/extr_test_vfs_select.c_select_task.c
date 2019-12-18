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
struct TYPE_2__ {scalar_t__ sem; int /*<<< orphan*/  select_ret; int /*<<< orphan*/  tv; int /*<<< orphan*/  errfds; int /*<<< orphan*/  wrfds; int /*<<< orphan*/  rdfds; int /*<<< orphan*/  maxfds; } ;
typedef  TYPE_1__ test_select_task_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (scalar_t__) ; 

__attribute__((used)) static void select_task(void *task_param)
{
    const test_select_task_param_t *param = task_param;

    int s = select(param->maxfds, param->rdfds, param->wrfds, param->errfds, param->tv);
    TEST_ASSERT_EQUAL(param->select_ret, s);

    if (param->sem) {
        xSemaphoreGive(param->sem);
    }
    vTaskDelete(NULL);
}