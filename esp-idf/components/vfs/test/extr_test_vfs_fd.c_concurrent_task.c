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
struct TYPE_2__ {int /*<<< orphan*/  done; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ concurrent_test_task_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int const,int) ; 
 int const close (int const) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_delay_rand_ms (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void concurrent_task(void *param)
{
    concurrent_test_task_param_t *task_param = (concurrent_test_task_param_t *) param;

    test_delay_rand_ms(10);
    for (int i = 0; i < 10; ++i) {
        const int global_fd = open(task_param->path, 0, 0);
        TEST_ASSERT_NOT_EQUAL(global_fd, -1);
        test_delay_rand_ms(10);
        TEST_ASSERT_NOT_EQUAL(close(global_fd), -1);
        test_delay_rand_ms(10);
    }
    xSemaphoreGive(task_param->done);
    vTaskDelete(NULL);
}