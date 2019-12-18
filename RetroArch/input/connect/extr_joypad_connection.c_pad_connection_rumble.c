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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* iface; int /*<<< orphan*/  connected; } ;
typedef  TYPE_2__ joypad_connection_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rumble ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool pad_connection_rumble(joypad_connection_t *joyconn,
   unsigned pad, enum retro_rumble_effect effect, uint16_t strength)
{
   if (!joyconn->connected)
      return false;
   if (!joyconn->iface || !joyconn->iface->set_rumble)
      return false;

   joyconn->iface->set_rumble(joyconn->data, effect, strength);
   return true;
}