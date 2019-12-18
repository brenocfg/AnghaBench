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
typedef  int /*<<< orphan*/  wiiu_hid_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  iface; int /*<<< orphan*/  connected; } ;
typedef  TYPE_1__ joypad_connection_t ;

/* Variables and functions */
 TYPE_1__* HID_PAD_CONNECTION_PTR (unsigned int) ; 
 int /*<<< orphan*/  wiiu_hid_joypad_query (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static joypad_connection_t *get_pad(wiiu_hid_t *hid, unsigned slot)
{
   if (!wiiu_hid_joypad_query(hid, slot))
      return NULL;

   joypad_connection_t *result = HID_PAD_CONNECTION_PTR(slot);
   if (!result || !result->connected || !result->iface || !result->data)
      return NULL;

   return result;
}