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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * osi_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/ * xSemaphoreCreateCounting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int osi_sem_new(osi_sem_t *sem, uint32_t max_count, uint32_t init_count)
{
    int ret = -1;

    if (sem) {
        *sem = xSemaphoreCreateCounting(max_count, init_count);
        if ((*sem) != NULL) {
            ret = 0;
        }
    }

    return ret;
}