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

/* Variables and functions */
 int TCI_FAIL_ASSERT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int crash_flags ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void failed_assert_task(void *pvParameter)
{
    printf("Task 'failed_assert_task' start.\n");
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("Task 'failed_assert_task' run.\n");
        if(crash_flags & TCI_FAIL_ASSERT) {
            printf("Assert.\n");
            assert(0);
        }
    }
    fflush(stdout);
}