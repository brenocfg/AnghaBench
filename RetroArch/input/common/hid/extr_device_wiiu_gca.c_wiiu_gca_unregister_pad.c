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
typedef  int /*<<< orphan*/  joypad_connection_t ;
struct TYPE_3__ {int /*<<< orphan*/ ** pads; } ;
typedef  TYPE_1__ hid_wiiu_gca_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  hid_pad_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiiu_gca_unregister_pad(hid_wiiu_gca_instance_t *instance, int slot)
{
   if(!instance || slot < 0 || slot >= 4 || instance->pads[slot] == NULL)
      return;

   joypad_connection_t *pad = instance->pads[slot];
   instance->pads[slot] = NULL;

   hid_pad_deregister(pad);
}