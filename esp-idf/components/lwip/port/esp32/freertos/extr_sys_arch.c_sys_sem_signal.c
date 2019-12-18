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
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 scalar_t__ errQUEUE_FULL ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xSemaphoreGive (int /*<<< orphan*/ ) ; 

void
sys_sem_signal(sys_sem_t *sem)
{
  BaseType_t ret = xSemaphoreGive(*sem);
  /* queue full is OK, this is a signal only... */
  LWIP_ASSERT("sys_sem_signal: sane return value",
             (ret == pdTRUE) || (ret == errQUEUE_FULL));
}