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
struct TYPE_3__ {void* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_THREAD_SAFE_DEBUG ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 

void
sys_mbox_set_owner(sys_mbox_t *mbox, void* owner)
{
  if (mbox && *mbox) {
    (*mbox)->owner = owner;
    LWIP_DEBUGF(ESP_THREAD_SAFE_DEBUG, ("set mbox=%p owner=%p", *mbox, owner));
  }
}