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
typedef  int /*<<< orphan*/  osi_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

void osi_sem_give(osi_sem_t *sem)
{
    xSemaphoreGive(*sem);
}