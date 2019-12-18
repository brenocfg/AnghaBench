#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sys_mbox_t ;
typedef  scalar_t__ UBaseType_t ;
struct TYPE_4__ {int /*<<< orphan*/  os_mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ uxQueueMessagesWaiting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ ) ; 

void
sys_mbox_free(sys_mbox_t *mbox)
{
  if ((NULL == mbox) || (NULL == *mbox)) {
    return;
  }
  UBaseType_t msgs_waiting = uxQueueMessagesWaiting((*mbox)->os_mbox);
  LWIP_ASSERT("mbox quence not empty", msgs_waiting == 0);

  vQueueDelete((*mbox)->os_mbox);
  free(*mbox);
  *mbox = NULL;
}