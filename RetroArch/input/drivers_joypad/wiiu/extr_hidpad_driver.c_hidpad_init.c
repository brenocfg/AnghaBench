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

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  hidpad_poll () ; 
 int hidpad_ready ; 
 int /*<<< orphan*/  init_hid_driver () ; 

__attribute__((used)) static bool hidpad_init(void *data)
{
   (void *)data;
   int i;

   if(!init_hid_driver())
   {
      RARCH_ERR("Failed to initialize HID driver.\n");
      return false;
   }

   hidpad_poll();
   hidpad_ready = true;

   return true;
}