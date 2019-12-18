#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct retro_keybind {unsigned int id; } ;
struct TYPE_4__ {unsigned int** input_remap_ids; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 int RARCH_FIRST_CUSTOM_BIND ; 
 TYPE_2__* config_get_ptr () ; 
 struct retro_keybind** input_config_binds ; 

__attribute__((used)) static int action_start_input_desc(unsigned type, const char *label)
{
   settings_t           *settings = config_get_ptr();
   unsigned inp_desc_index_offset = type - MENU_SETTINGS_INPUT_DESC_BEGIN;
   unsigned inp_desc_user         = inp_desc_index_offset / (RARCH_FIRST_CUSTOM_BIND + 4);
   unsigned inp_desc_button_index_offset = inp_desc_index_offset - (inp_desc_user * (RARCH_FIRST_CUSTOM_BIND + 4));

   (void)label;

   if (inp_desc_button_index_offset < RARCH_FIRST_CUSTOM_BIND)
   {
      const struct retro_keybind *keyptr = &input_config_binds[inp_desc_user]
            [inp_desc_button_index_offset];
      settings->uints.input_remap_ids[inp_desc_user][inp_desc_button_index_offset] = keyptr->id;
   }
   else
      settings->uints.input_remap_ids[inp_desc_user][inp_desc_button_index_offset] =
         inp_desc_button_index_offset - RARCH_FIRST_CUSTOM_BIND;

   return 0;
}