#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* query_pad ) (unsigned int) ;} ;
struct TYPE_3__ {int connected; } ;

/* Variables and functions */
 TYPE_2__ dinput_joypad ; 
 TYPE_1__* g_xinput_states ; 
 int pad_index_to_xuser_index (unsigned int) ; 
 int stub1 (unsigned int) ; 

__attribute__((used)) static bool xinput_joypad_query_pad(unsigned pad)
{
   int xuser = pad_index_to_xuser_index(pad);
   if (xuser > -1)
      return g_xinput_states[xuser].connected;
#ifdef HAVE_DINPUT
   return dinput_joypad.query_pad(pad);
#else
   return false;
#endif
}