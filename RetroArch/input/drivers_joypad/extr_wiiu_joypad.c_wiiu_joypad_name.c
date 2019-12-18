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
struct TYPE_2__ {char const* (* name ) (unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__** pad_drivers ; 
 char const* stub1 (unsigned int) ; 
 int /*<<< orphan*/  wiiu_joypad_query_pad (unsigned int) ; 

__attribute__((used)) static const char* wiiu_joypad_name(unsigned pad)
{
   if (!wiiu_joypad_query_pad(pad))
      return "N/A";

   return pad_drivers[pad]->name(pad);
}