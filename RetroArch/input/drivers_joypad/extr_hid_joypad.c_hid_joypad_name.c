#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* (* name ) (void*,unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__* generic_hid ; 
 scalar_t__ hid_driver_get_data () ; 
 char const* stub1 (void*,unsigned int) ; 

__attribute__((used)) static const char *hid_joypad_name(unsigned pad)
{
   if (generic_hid && generic_hid->name)
      return generic_hid->name((void*)hid_driver_get_data(), pad);
   return NULL;
}