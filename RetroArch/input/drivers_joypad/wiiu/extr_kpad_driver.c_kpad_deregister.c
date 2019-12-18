#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pad_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* name ) (int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIMOTE_TYPE_NONE ; 
 int* channel_slot_map ; 
 TYPE_4__ hid_instance ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ kpad_driver ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_2__* wiimotes ; 

__attribute__((used)) static void kpad_deregister(unsigned channel)
{
   int slot = channel_slot_map[channel];

   if(slot >= 0)
   {
      input_autoconfigure_disconnect(slot, kpad_driver.name(slot));
      wiimotes[channel].type = WIIMOTE_TYPE_NONE;
      hid_instance.pad_list[slot].connected = false;
      channel_slot_map[channel] = -1;
   }
}