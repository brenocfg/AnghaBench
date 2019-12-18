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
struct TYPE_2__ {char const* ident; } ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 TYPE_1__* linuxraw_pads ; 
 scalar_t__ string_is_empty (char const*) ; 

__attribute__((used)) static const char *linuxraw_joypad_name(unsigned pad)
{
   if (pad >= MAX_USERS || string_is_empty(linuxraw_pads[pad].ident))
      return NULL;

   return linuxraw_pads[pad].ident;
}