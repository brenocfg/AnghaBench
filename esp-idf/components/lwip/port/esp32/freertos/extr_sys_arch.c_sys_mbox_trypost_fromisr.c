#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sys_mbox_t ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_mbox; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_NEED_SCHED ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 scalar_t__ errQUEUE_FULL ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xQueueSendFromISR (int /*<<< orphan*/ ,void**,scalar_t__*) ; 

err_t
sys_mbox_trypost_fromisr(sys_mbox_t *mbox, void *msg)
{
  BaseType_t ret;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  ret = xQueueSendFromISR((*mbox)->os_mbox, &msg, &xHigherPriorityTaskWoken);
  if (ret == pdTRUE) {
    if (xHigherPriorityTaskWoken == pdTRUE) {
      return ERR_NEED_SCHED;
    }
    return ERR_OK;
  } else {
    LWIP_ASSERT("mbox trypost failed", ret == errQUEUE_FULL);
    return ERR_MEM;
  }
}