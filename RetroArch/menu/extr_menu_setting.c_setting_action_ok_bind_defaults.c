#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_keybind {void* mbutton; int /*<<< orphan*/  joyaxis; void* joykey; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {size_t index_offset; } ;
typedef  TYPE_1__ rarch_setting_t ;
struct TYPE_6__ {unsigned int min; unsigned int max; } ;
typedef  TYPE_2__ menu_input_ctx_bind_limits_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 unsigned int MENU_SETTINGS_BIND_BEGIN ; 
 unsigned int MENU_SETTINGS_BIND_LAST ; 
 void* NO_BTN ; 
 struct retro_keybind** input_config_binds ; 
 int /*<<< orphan*/  menu_input_key_bind_set_min_max (TYPE_2__*) ; 
 struct retro_keybind* retro_keybinds_1 ; 
 struct retro_keybind* retro_keybinds_rest ; 

__attribute__((used)) static int setting_action_ok_bind_defaults(rarch_setting_t *setting, bool wraparound)
{
   unsigned i;
   menu_input_ctx_bind_limits_t lim;
   struct retro_keybind *target          = NULL;
   const struct retro_keybind *def_binds = NULL;

   (void)wraparound;

   if (!setting)
      return -1;

   target    =  &input_config_binds[setting->index_offset][0];
   def_binds =  (setting->index_offset) ?
      retro_keybinds_rest : retro_keybinds_1;

   lim.min   = MENU_SETTINGS_BIND_BEGIN;
   lim.max   = MENU_SETTINGS_BIND_LAST;

   menu_input_key_bind_set_min_max(&lim);

   for (i = MENU_SETTINGS_BIND_BEGIN;
         i <= MENU_SETTINGS_BIND_LAST; i++, target++)
   {
      target->key     = def_binds[i - MENU_SETTINGS_BIND_BEGIN].key;
      target->joykey  = NO_BTN;
      target->joyaxis = AXIS_NONE;
      target->mbutton = NO_BTN;
   }

   return 0;
}