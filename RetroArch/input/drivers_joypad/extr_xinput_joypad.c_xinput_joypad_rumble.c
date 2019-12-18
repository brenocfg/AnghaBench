#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_5__ {int (* set_rumble ) (unsigned int,int,void*) ;} ;
struct TYPE_4__ {void* wRightMotorSpeed; void* wLeftMotorSpeed; } ;

/* Variables and functions */
 int RETRO_RUMBLE_STRONG ; 
 int RETRO_RUMBLE_WEAK ; 
 TYPE_3__ dinput_joypad ; 
 scalar_t__ g_XInputSetState (int,TYPE_1__*) ; 
 TYPE_1__* g_xinput_rumble_states ; 
 int pad_index_to_xuser_index (unsigned int) ; 
 int stub1 (unsigned int,int,void*) ; 

__attribute__((used)) static bool xinput_joypad_rumble(unsigned pad,
      enum retro_rumble_effect effect, uint16_t strength)
{
   int xuser = pad_index_to_xuser_index(pad);

   if (xuser == -1)
   {
#ifdef HAVE_DINPUT
      if (dinput_joypad.set_rumble)
         return dinput_joypad.set_rumble(pad, effect, strength);
#endif
      return false;
   }

   /* Consider the low frequency (left) motor the "strong" one. */
   if (effect == RETRO_RUMBLE_STRONG)
      g_xinput_rumble_states[xuser].wLeftMotorSpeed = strength;
   else if (effect == RETRO_RUMBLE_WEAK)
      g_xinput_rumble_states[xuser].wRightMotorSpeed = strength;

   if (!g_XInputSetState)
      return false;

   return (g_XInputSetState(xuser, &g_xinput_rumble_states[xuser])
      == 0);
}