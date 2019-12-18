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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int (* button ) (unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__** pad_drivers ; 
 int stub1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiu_joypad_query_pad (unsigned int) ; 

__attribute__((used)) static bool wiiu_joypad_button(unsigned pad, uint16_t key)
{
   if (!wiiu_joypad_query_pad(pad))
      return false;

   return pad_drivers[pad]->button(pad, key);
}