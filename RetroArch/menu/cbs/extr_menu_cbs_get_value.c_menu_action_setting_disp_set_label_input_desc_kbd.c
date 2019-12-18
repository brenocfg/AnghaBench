#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int** input_keymapper_ids; } ;
struct TYPE_6__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_7__ {unsigned int key; char* desc; } ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_BEGIN ; 
 int PATH_MAX_LENGTH ; 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 int RARCH_MAX_KEYS ; 
 unsigned int RETROK_FIRST ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_3__* key_descriptors ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_input_desc_kbd(
   file_list_t* list,
   unsigned *w, unsigned type, unsigned i,
   const char *label,
   char *s, size_t len,
   const char *path,
   char *s2, size_t len2)
{
   char desc[PATH_MAX_LENGTH];
   unsigned key_id, btn_idx;
   unsigned remap_id;
   unsigned user_idx = 0;

   settings_t *settings = config_get_ptr();

   if (!settings)
      return;

   user_idx = (type - MENU_SETTINGS_INPUT_DESC_KBD_BEGIN) / RARCH_FIRST_CUSTOM_BIND;
   btn_idx  = (type - MENU_SETTINGS_INPUT_DESC_KBD_BEGIN) - RARCH_FIRST_CUSTOM_BIND * user_idx;
   remap_id =
      settings->uints.input_keymapper_ids[user_idx][btn_idx];

   for (key_id = 0; key_id < RARCH_MAX_KEYS - 1; key_id++)
   {
      if (remap_id == key_descriptors[key_id].key)
         break;
   }

   if (key_descriptors[key_id].key != RETROK_FIRST)
   {
      snprintf(desc, sizeof(desc), "Keyboard %s", key_descriptors[key_id].desc);
      strlcpy(s, desc, len);
   }
   else
      strlcpy(s, "---", len);

   *w = 19;
   strlcpy(s2, path, len2);
}