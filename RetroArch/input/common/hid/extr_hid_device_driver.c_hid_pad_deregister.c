#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int connected; TYPE_1__* iface; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ joypad_connection_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void hid_pad_deregister(joypad_connection_t *pad)
{
   if(!pad)
      return;

   if(pad->data) {
      pad->iface->deinit(pad->data);
      pad->data = NULL;
   }

   pad->iface = NULL;
   pad->connected = false;
}