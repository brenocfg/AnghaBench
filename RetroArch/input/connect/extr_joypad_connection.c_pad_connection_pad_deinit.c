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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int connected; TYPE_1__* iface; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ joypad_connection_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_rumble ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_RUMBLE_STRONG ; 
 int /*<<< orphan*/  RETRO_RUMBLE_WEAK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

void pad_connection_pad_deinit(joypad_connection_t *joyconn, uint32_t pad)
{
   if (!joyconn || !joyconn->connected)
       return;

   if (joyconn->iface)
   {
      joyconn->iface->set_rumble(joyconn->data, RETRO_RUMBLE_STRONG, 0);
      joyconn->iface->set_rumble(joyconn->data, RETRO_RUMBLE_WEAK, 0);

      if (joyconn->iface->deinit)
         joyconn->iface->deinit(joyconn->data);
   }

   joyconn->iface     = NULL;
   joyconn->connected = false;
}