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
typedef  int /*<<< orphan*/  file_list_t ;
typedef  int /*<<< orphan*/  core_option_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_DISABLED ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ENABLED ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_OFF ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ON ; 
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTIONS_LIST_GET ; 
 char* core_option_manager_get_val_label (int /*<<< orphan*/ *,unsigned int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_core_options(file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   core_option_manager_t *coreopts = NULL;
   const char *core_opt = NULL;

   *s = '\0';
   *w = 19;

   if (rarch_ctl(RARCH_CTL_CORE_OPTIONS_LIST_GET, &coreopts))
   {
      core_opt = core_option_manager_get_val_label(coreopts,
            type - MENU_SETTINGS_CORE_OPTION_START);

      strlcpy(s, "", len);

      if (core_opt)
      {
         if (string_is_equal(core_opt, msg_hash_to_str(MENU_ENUM_LABEL_ENABLED)))
            core_opt = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ON);
         else if (string_is_equal(core_opt, msg_hash_to_str(MENU_ENUM_LABEL_DISABLED)))
            core_opt = msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF);
         strlcpy(s, core_opt, len);
      }
   }

   strlcpy(s2, path, len2);
}