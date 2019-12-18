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
struct TYPE_6__ {unsigned int** input_remap_ids; } ;
struct TYPE_7__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {char*** input_desc_btn; } ;
typedef  TYPE_3__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RARCH_UNMAPPED ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_3__* runloop_get_system_info () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_input_desc(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   rarch_system_info_t *system           = runloop_get_system_info();
   settings_t *settings                  = config_get_ptr();
   const char* descriptor                = NULL;
   char buf[256];

   unsigned btn_idx, user_idx, remap_idx;

   if (!settings)
      return;

   user_idx  = (type - MENU_SETTINGS_INPUT_DESC_BEGIN) / (RARCH_FIRST_CUSTOM_BIND + 8);
   btn_idx   = (type - MENU_SETTINGS_INPUT_DESC_BEGIN) - (RARCH_FIRST_CUSTOM_BIND + 8) * user_idx;
   remap_idx =
      settings->uints.input_remap_ids[user_idx][btn_idx];

   if (!system)
      return;

   if (remap_idx != RARCH_UNMAPPED)
      descriptor = system->input_desc_btn[user_idx][remap_idx];

   if (!string_is_empty(descriptor) && remap_idx < RARCH_FIRST_CUSTOM_BIND)
      strlcpy(s, descriptor, len);
   else if (!string_is_empty(descriptor) && remap_idx >= RARCH_FIRST_CUSTOM_BIND && remap_idx % 2 == 0)
   {
      snprintf(buf, sizeof(buf), "%s %c", descriptor, '+');
      strlcpy(s, buf, len);
   }
   else if (!string_is_empty(descriptor) && remap_idx >= RARCH_FIRST_CUSTOM_BIND && remap_idx % 2 != 0)
   {
      snprintf(buf, sizeof(buf), "%s %c", descriptor, '-');
      strlcpy(s, buf, len);
   }
   else
      strlcpy(s, "---", len);

   *w = 19;
   strlcpy(s2, path, len2);
}