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
struct item_cheat {int rumble_type; unsigned int rumble_prev_value; unsigned int rumble_value; int rumble_initialized; scalar_t__ rumble_primary_end_time; int rumble_primary_duration; scalar_t__ rumble_secondary_end_time; int rumble_secondary_duration; int /*<<< orphan*/  rumble_secondary_strength; int /*<<< orphan*/  rumble_port; int /*<<< orphan*/  rumble_primary_strength; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_RUMBLE_STRONG ; 
 int /*<<< orphan*/  RETRO_RUMBLE_WEAK ; 
#define  RUMBLE_TYPE_CHANGES 138 
#define  RUMBLE_TYPE_DECREASE 137 
#define  RUMBLE_TYPE_DECREASE_BY_VALUE 136 
#define  RUMBLE_TYPE_DISABLED 135 
#define  RUMBLE_TYPE_DOES_NOT_CHANGE 134 
#define  RUMBLE_TYPE_EQ_VALUE 133 
#define  RUMBLE_TYPE_GT_VALUE 132 
#define  RUMBLE_TYPE_INCREASE 131 
#define  RUMBLE_TYPE_INCREASE_BY_VALUE 130 
#define  RUMBLE_TYPE_LT_VALUE 129 
#define  RUMBLE_TYPE_NEQ_VALUE 128 
 scalar_t__ cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  input_driver_set_rumble_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cheat_manager_apply_rumble(struct item_cheat *cheat, unsigned int curr_value)
{
   bool rumble = false;

   switch (cheat->rumble_type)
   {
      case RUMBLE_TYPE_DISABLED:
         return;
      case RUMBLE_TYPE_CHANGES:
         rumble = (curr_value != cheat->rumble_prev_value);
         break;
      case RUMBLE_TYPE_DOES_NOT_CHANGE:
         rumble = (curr_value == cheat->rumble_prev_value);
         break;
      case RUMBLE_TYPE_INCREASE:
         rumble = (curr_value > cheat->rumble_prev_value);
         break;
      case RUMBLE_TYPE_DECREASE:
         rumble = (curr_value < cheat->rumble_prev_value);
         break;
      case RUMBLE_TYPE_EQ_VALUE:
         rumble = (curr_value == cheat->rumble_value);
         break;
      case RUMBLE_TYPE_NEQ_VALUE:
         rumble = (curr_value != cheat->rumble_value);
         break;
      case RUMBLE_TYPE_LT_VALUE:
         rumble = (curr_value < cheat->rumble_value);
         break;
      case RUMBLE_TYPE_GT_VALUE:
         rumble = (curr_value > cheat->rumble_value);
         break;
      case RUMBLE_TYPE_INCREASE_BY_VALUE:
         rumble = (curr_value == cheat->rumble_prev_value + cheat->rumble_value);
         break;
      case RUMBLE_TYPE_DECREASE_BY_VALUE:
         rumble = (curr_value == cheat->rumble_prev_value - cheat->rumble_value);
         break;
   }

   cheat->rumble_prev_value = curr_value;

   /* Give the emulator enough time
    * to initialize, load state, etc */
   if (cheat->rumble_initialized > 300)
   {
      if (rumble)
      {
         cheat->rumble_primary_end_time = cpu_features_get_time_usec() + (cheat->rumble_primary_duration * 1000);
         cheat->rumble_secondary_end_time = cpu_features_get_time_usec() + (cheat->rumble_secondary_duration * 1000);
         input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_STRONG, cheat->rumble_primary_strength);
         input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_WEAK, cheat->rumble_secondary_strength);
      }
   }
   else
   {
      cheat->rumble_initialized++;
      return;
   }

   if (cheat->rumble_primary_end_time <= cpu_features_get_time_usec())
   {
      if (cheat->rumble_primary_end_time != 0)
         input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_STRONG, 0);
      cheat->rumble_primary_end_time = 0;
   }
   else
   {
      input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_STRONG, cheat->rumble_primary_strength);
   }

   if (cheat->rumble_secondary_end_time <= cpu_features_get_time_usec())
   {
      if (cheat->rumble_secondary_end_time != 0)
         input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_WEAK, 0);
      cheat->rumble_secondary_end_time = 0;
   }
   else
      input_driver_set_rumble_state(cheat->rumble_port, RETRO_RUMBLE_WEAK, cheat->rumble_secondary_strength);
}