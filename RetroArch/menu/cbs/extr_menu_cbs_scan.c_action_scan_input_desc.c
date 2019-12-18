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
struct retro_keybind {void* mbutton; int /*<<< orphan*/  joyaxis; void* joykey; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 void* NO_BTN ; 
 int /*<<< orphan*/  RETROK_UNKNOWN ; 
 unsigned char atoi (char const*) ; 
 struct retro_keybind** input_config_binds ; 
 unsigned int input_config_translate_str_to_bind_id (char const*) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static int action_scan_input_desc(const char *path,
      const char *label, unsigned type, size_t idx)
{
   const char *menu_label         = NULL;
   unsigned key                   = 0;
   unsigned inp_desc_user         = 0;
   struct retro_keybind *target   = NULL;

   menu_entries_get_last_stack(NULL, &menu_label, NULL, NULL, NULL);

   if (string_is_equal(menu_label, "deferred_user_binds_list"))
   {
      unsigned char player_no_str = atoi(&label[1]);

      inp_desc_user      = (unsigned)(player_no_str - 1);
      /* This hardcoded value may cause issues if any entries are added on
         top of the input binds */
      key                = (unsigned)(idx - 7);
   }
   else
      key = input_config_translate_str_to_bind_id(label);

   target = &input_config_binds[inp_desc_user][key];

   if (target)
   {
      target->key     = RETROK_UNKNOWN;
      target->joykey  = NO_BTN;
      target->joyaxis = AXIS_NONE;
      target->mbutton = NO_BTN;
   }

   return 0;
}