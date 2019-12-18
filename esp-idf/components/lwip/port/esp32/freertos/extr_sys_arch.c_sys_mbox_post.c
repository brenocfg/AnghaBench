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
struct TYPE_3__ {int /*<<< orphan*/  os_mbox; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ xQueueSendToBack (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 

void
sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
  BaseType_t ret = xQueueSendToBack((*mbox)->os_mbox, &msg, portMAX_DELAY);
  LWIP_ASSERT("mbox post failed", ret == pdTRUE);
}