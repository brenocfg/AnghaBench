#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int id; int /*<<< orphan*/  rumble_last_strength; int /*<<< orphan*/  rumble_last_strength_weak; int /*<<< orphan*/  rumble_last_strength_strong; } ;
typedef  TYPE_2__ state_device_t ;
struct TYPE_7__ {scalar_t__ enable_device_vibration; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_10__ {TYPE_2__* pad_states; } ;
typedef  TYPE_4__ android_input_t ;
struct TYPE_11__ {int /*<<< orphan*/  doVibrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  android_input_set_rumble_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 TYPE_5__* g_android ; 

__attribute__((used)) static bool android_input_set_rumble(void *data, unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
   settings_t *settings = config_get_ptr();

   if (!g_android || !g_android->doVibrate)
      return false;

   if (settings->bools.enable_device_vibration)
   {
      static uint16_t last_strength_strong = 0;
      static uint16_t last_strength_weak   = 0;
      static uint16_t last_strength        = 0;

      if (port != 0)
         return false;
      
      android_input_set_rumble_internal(
            strength,
            &last_strength_strong,
            &last_strength_weak,
            &last_strength,
            -1,
            effect);

      return true;
   }
   else
   {
      android_input_t *android = (android_input_t*)data;
      state_device_t *state    = android ? &android->pad_states[port] : NULL;

      if (state)
      {
         android_input_set_rumble_internal(
               strength,
               &state->rumble_last_strength_strong,
               &state->rumble_last_strength_weak,
               &state->rumble_last_strength,
               state->id,
               effect);
         return true;
      }
   }

   return false;
}