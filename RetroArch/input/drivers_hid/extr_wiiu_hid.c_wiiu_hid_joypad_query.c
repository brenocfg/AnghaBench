#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_hid_t ;

/* Variables and functions */
 unsigned int HID_MAX_SLOT () ; 

__attribute__((used)) static bool wiiu_hid_joypad_query(void *data, unsigned slot)
{
   wiiu_hid_t *hid = (wiiu_hid_t *)data;
   if (!hid)
      return false;

   return slot < HID_MAX_SLOT();
}