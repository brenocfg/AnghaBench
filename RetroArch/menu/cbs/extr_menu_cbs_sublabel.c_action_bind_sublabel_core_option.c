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
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTIONS_LIST_GET ; 
 char* core_option_manager_get_info (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int action_bind_sublabel_core_option(
      file_list_t *list,
      unsigned type, unsigned i,
      const char *label, const char *path,
      char *s, size_t len)
{
   core_option_manager_t *opt = NULL;
   const char *info           = NULL;

   if (!rarch_ctl(RARCH_CTL_CORE_OPTIONS_LIST_GET, &opt))
      return 0;

   info = core_option_manager_get_info(opt, type - MENU_SETTINGS_CORE_OPTION_START);

   if (!string_is_empty(info))
      strlcpy(s, info, len);

   return 0;
}