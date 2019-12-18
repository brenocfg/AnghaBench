#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int* gamepads; } ;
typedef  TYPE_2__ xdk_input_t ;
typedef  void* uint16_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_6__ {void* wRightMotorSpeed; void* wLeftMotorSpeed; } ;
struct TYPE_8__ {TYPE_1__ Rumble; void* wRightMotorSpeed; void* wLeftMotorSpeed; } ;
typedef  TYPE_3__ XINPUT_VIBRATION ;
typedef  TYPE_3__ XINPUT_FEEDBACK ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int RETRO_RUMBLE_STRONG ; 
 int RETRO_RUMBLE_WEAK ; 
 scalar_t__ XInputSetState (unsigned int,TYPE_3__*) ; 

__attribute__((used)) static bool xdk_input_set_rumble(void *data, unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
#ifdef _XBOX360
#if 0
   XINPUT_VIBRATION rumble_state;
#endif
#endif
   xdk_input_t *xdk = (xdk_input_t*)data;
   bool val         = false;

   (void)xdk;

#if 0
#if defined(_XBOX360)
   if (effect == RETRO_RUMBLE_STRONG)
      rumble_state.wLeftMotorSpeed = strength;
   else if (effect == RETRO_RUMBLE_WEAK)
      rumble_state.wRightMotorSpeed = strength;
   val = XInputSetState(port, &rumble_state) == ERROR_SUCCESS;
#elif defined(_XBOX1)
#if 0
   XINPUT_FEEDBACK rumble_state;

   if (effect == RETRO_RUMBLE_STRONG)
      rumble_state.Rumble.wLeftMotorSpeed = strength;
   else if (effect == RETRO_RUMBLE_WEAK)
      rumble_state.Rumble.wRightMotorSpeed = strength;
   val = XInputSetState(xdk->gamepads[port], &rumble_state) == ERROR_SUCCESS;
#endif
#endif
#endif
   return val;
}