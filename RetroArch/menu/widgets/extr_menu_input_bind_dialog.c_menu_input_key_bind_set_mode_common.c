#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct retro_keybind {int dummy; } ;
struct TYPE_12__ {scalar_t__ keybind; } ;
struct TYPE_13__ {TYPE_1__ target; } ;
struct TYPE_14__ {unsigned int index_offset; TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;
struct TYPE_15__ {size_t directory_ptr; void* label; void* enum_idx; void* type; int /*<<< orphan*/ * list; } ;
typedef  TYPE_4__ menu_displaylist_info_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum menu_input_binds_ctl_state { ____Placeholder_menu_input_binds_ctl_state } menu_input_binds_ctl_state ;
struct TYPE_16__ {unsigned int begin; unsigned int last; unsigned int user; struct retro_keybind* output; struct retro_keybind buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_INFO ; 
 void* MENU_ENUM_LABEL_CUSTOM_BIND ; 
 void* MENU_ENUM_LABEL_CUSTOM_BIND_ALL ; 
#define  MENU_INPUT_BINDS_CTL_BIND_ALL 130 
#define  MENU_INPUT_BINDS_CTL_BIND_NONE 129 
#define  MENU_INPUT_BINDS_CTL_BIND_SINGLE 128 
 unsigned int MENU_SETTINGS_BIND_BEGIN ; 
 unsigned int MENU_SETTINGS_BIND_LAST ; 
 void* MENU_SETTINGS_CUSTOM_BIND_KEYBOARD ; 
 struct retro_keybind** input_config_binds ; 
 int /*<<< orphan*/  menu_displaylist_ctl (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_free (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_init (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_displaylist_process (TYPE_4__*) ; 
 int /*<<< orphan*/ * menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 TYPE_7__ menu_input_binds ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  msg_hash_to_str (void*) ; 
 unsigned int setting_get_bind_type (TYPE_3__*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menu_input_key_bind_set_mode_common(
      enum menu_input_binds_ctl_state state,
      rarch_setting_t  *setting)
{
   menu_displaylist_info_t info;
   unsigned bind_type            = 0;
   struct retro_keybind *keybind = NULL;
   unsigned         index_offset = setting->index_offset;
   file_list_t *menu_stack       = menu_entries_get_menu_stack_ptr(0);
   size_t selection              = menu_navigation_get_selection();

   menu_displaylist_info_init(&info);

   switch (state)
   {
      case MENU_INPUT_BINDS_CTL_BIND_SINGLE:
         keybind    = (struct retro_keybind*)setting->value.target.keybind;

         if (!keybind)
            return -1;

         bind_type                = setting_get_bind_type(setting);

         menu_input_binds.begin   = bind_type;
         menu_input_binds.last    = bind_type;
         menu_input_binds.output  = keybind;
         menu_input_binds.buffer  = *(menu_input_binds.output);
         menu_input_binds.user    = index_offset;

         info.list                = menu_stack;
         info.type                = MENU_SETTINGS_CUSTOM_BIND_KEYBOARD;
         info.directory_ptr       = selection;
         info.enum_idx            = MENU_ENUM_LABEL_CUSTOM_BIND;
         info.label               = strdup(
               msg_hash_to_str(MENU_ENUM_LABEL_CUSTOM_BIND));
         if (menu_displaylist_ctl(DISPLAYLIST_INFO, &info))
            menu_displaylist_process(&info);
         menu_displaylist_info_free(&info);
         break;
      case MENU_INPUT_BINDS_CTL_BIND_ALL:
         menu_input_binds.output  = &input_config_binds[index_offset][0];
         menu_input_binds.buffer  = *(menu_input_binds.output);
         menu_input_binds.begin   = MENU_SETTINGS_BIND_BEGIN;
         menu_input_binds.last    = MENU_SETTINGS_BIND_LAST;

         info.list                = menu_stack;
         info.type                = MENU_SETTINGS_CUSTOM_BIND_KEYBOARD;
         info.directory_ptr       = selection;
         info.enum_idx            = MENU_ENUM_LABEL_CUSTOM_BIND_ALL;
         info.label               = strdup(
               msg_hash_to_str(MENU_ENUM_LABEL_CUSTOM_BIND_ALL));

         if (menu_displaylist_ctl(DISPLAYLIST_INFO, &info))
            menu_displaylist_process(&info);
         menu_displaylist_info_free(&info);
         break;
      default:
      case MENU_INPUT_BINDS_CTL_BIND_NONE:
         break;
   }

   return 0;
}