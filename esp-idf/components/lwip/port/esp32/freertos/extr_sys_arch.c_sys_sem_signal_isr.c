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
typedef  int /*<<< orphan*/  sys_sem_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  xSemaphoreGiveFromISR (int /*<<< orphan*/ ,scalar_t__*) ; 

int
sys_sem_signal_isr(sys_sem_t *sem)
{
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(*sem, &woken);
    return woken == pdTRUE;
}