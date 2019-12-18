#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_21__ {scalar_t__ menu_show_core_updater; } ;
struct TYPE_17__ {int /*<<< orphan*/  directory_system; } ;
struct TYPE_22__ {TYPE_6__ bools; TYPE_2__ paths; } ;
typedef  TYPE_7__ settings_t ;
struct TYPE_23__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_8__ menu_displaylist_info_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
struct TYPE_24__ {char const* core_name; char const* display_name; char const* systemname; char const* system_manufacturer; unsigned int firmware_count; TYPE_5__* note_list; scalar_t__ notes; TYPE_3__* firmware; int /*<<< orphan*/  path; scalar_t__ required_hw_api_list; scalar_t__ required_hw_api; scalar_t__ supported_extensions_list; scalar_t__ licenses_list; scalar_t__ permissions_list; scalar_t__ authors_list; scalar_t__ categories_list; int /*<<< orphan*/  config_data; } ;
typedef  TYPE_9__ core_info_t ;
struct TYPE_16__ {int /*<<< orphan*/  system; } ;
struct TYPE_15__ {TYPE_1__ directory; int /*<<< orphan*/  path; } ;
typedef  TYPE_10__ core_info_ctx_firmware_t ;
struct TYPE_20__ {unsigned int size; TYPE_4__* elems; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {char* desc; scalar_t__ optional; scalar_t__ missing; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct menu_features_info*) ; 
 int MENU_ENUM_LABEL_CORE_DELETE ; 
 int MENU_ENUM_LABEL_CORE_INFO_ENTRY ; 
 int MENU_ENUM_LABEL_NO_CORE_INFORMATION_AVAILABLE ; 
 int MENU_ENUM_LABEL_VALUE_CORE_DELETE ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_AUTHORS ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_CATEGORIES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_INFO_CORE_LABEL ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_INFO_CORE_NAME ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_FIRMWARE ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_LICENSES ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_PERMISSIONS ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_REQUIRED_HW_API ; 
 int MENU_ENUM_LABEL_VALUE_CORE_INFO_SUPPORTED_EXTENSIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_INFO_SYSTEM_MANUFACTURER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_INFO_SYSTEM_NAME ; 
 int MENU_ENUM_LABEL_VALUE_MISSING ; 
 int MENU_ENUM_LABEL_VALUE_NO_CORE_INFORMATION_AVAILABLE ; 
 int MENU_ENUM_LABEL_VALUE_OPTIONAL ; 
 int MENU_ENUM_LABEL_VALUE_PRESENT ; 
 int MENU_ENUM_LABEL_VALUE_RDB_ENTRY_NAME ; 
 int MENU_ENUM_LABEL_VALUE_REQUIRED ; 
 int /*<<< orphan*/  MENU_SETTINGS_CORE_INFO_NONE ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_CORE_DELETE ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_CTL_SET_MISSING_BIOS ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_MISSING_BIOS ; 
 TYPE_7__* config_get_ptr () ; 
 int /*<<< orphan*/  core_info_get_current_core (TYPE_9__**) ; 
 int core_info_list_update_missing_firmware (TYPE_10__*,int*) ; 
 int /*<<< orphan*/  fill_pathname_join_concat_noext (char*,char*,char*,char const*,int) ; 
 int /*<<< orphan*/  fill_pathname_noext (char*,char*,char*,int) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  string_list_join_concat (char*,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int menu_displaylist_parse_core_info(menu_displaylist_info_t *info)
{
   unsigned i;
   char tmp[PATH_MAX_LENGTH];
   core_info_t *core_info    = NULL;
   settings_t *settings      = config_get_ptr();

   tmp[0] = '\0';

   core_info_get_current_core(&core_info);

   if (!core_info || !core_info->config_data)
   {
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_CORE_INFORMATION_AVAILABLE),
            msg_hash_to_str(MENU_ENUM_LABEL_NO_CORE_INFORMATION_AVAILABLE),
            MENU_ENUM_LABEL_NO_CORE_INFORMATION_AVAILABLE,
            0, 0, 0);
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_DELETE),
            msg_hash_to_str(MENU_ENUM_LABEL_CORE_DELETE),
            MENU_ENUM_LABEL_CORE_DELETE,
            MENU_SETTING_ACTION_CORE_DELETE, 0, 0);

      return 0;
   }

   {
      unsigned i;
      typedef struct menu_features_info
      {
         const char *name;
         enum msg_hash_enums msg;
      } menu_features_info_t;

      menu_features_info_t info_list[] = {
         {NULL, MENU_ENUM_LABEL_VALUE_CORE_INFO_CORE_NAME},
         {NULL, MENU_ENUM_LABEL_VALUE_CORE_INFO_CORE_LABEL},
         {NULL, MENU_ENUM_LABEL_VALUE_CORE_INFO_SYSTEM_NAME},
         {NULL, MENU_ENUM_LABEL_VALUE_CORE_INFO_SYSTEM_MANUFACTURER},
      };
      info_list[0].name = core_info->core_name;
      info_list[1].name = core_info->display_name;
      info_list[2].name = core_info->systemname;
      info_list[3].name = core_info->system_manufacturer;

      for (i = 0; i < ARRAY_SIZE(info_list); i++)
      {
         if (!info_list[i].name)
            continue;

         fill_pathname_join_concat_noext(tmp,
               msg_hash_to_str(info_list[i].msg),
               ": ",
               info_list[i].name,
               sizeof(tmp));
         menu_entries_append_enum(info->list, tmp, "",
               MENU_ENUM_LABEL_CORE_INFO_ENTRY,
               MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
      }
   }

   if (core_info->categories_list)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_CATEGORIES),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->categories_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->authors_list)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_AUTHORS),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->authors_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->permissions_list)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_PERMISSIONS),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->permissions_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->licenses_list)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_LICENSES),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->licenses_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->supported_extensions_list)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_SUPPORTED_EXTENSIONS),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->supported_extensions_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->required_hw_api)
   {
      fill_pathname_noext(tmp,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_REQUIRED_HW_API),
            ": ",
            sizeof(tmp));
      string_list_join_concat(tmp, sizeof(tmp),
            core_info->required_hw_api_list, ", ");
      menu_entries_append_enum(info->list, tmp, "",
            MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
   }

   if (core_info->firmware_count > 0)
   {
      core_info_ctx_firmware_t firmware_info;
      bool update_missing_firmware   = false;
      bool set_missing_firmware      = false;

      firmware_info.path             = core_info->path;
      firmware_info.directory.system = settings->paths.directory_system;

      rarch_ctl(RARCH_CTL_UNSET_MISSING_BIOS, NULL);

      update_missing_firmware        = core_info_list_update_missing_firmware(&firmware_info, &set_missing_firmware);

      if (set_missing_firmware)
         rarch_ctl(RARCH_CTL_SET_MISSING_BIOS, NULL);

      if (update_missing_firmware)
      {
         fill_pathname_noext(tmp,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INFO_FIRMWARE),
               ": ",
               sizeof(tmp));
         menu_entries_append_enum(info->list, tmp, "",
               MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);

         /* FIXME: This looks hacky and probably
          * needs to be improved for good translation support. */

         for (i = 0; i < core_info->firmware_count; i++)
         {
            if (!core_info->firmware[i].desc)
               continue;

            snprintf(tmp, sizeof(tmp), "(!) %s, %s: %s",
                  core_info->firmware[i].missing ?
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_MISSING) :
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PRESENT),
                  core_info->firmware[i].optional ?
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OPTIONAL) :
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_REQUIRED),
                  core_info->firmware[i].desc ?
                  core_info->firmware[i].desc :
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RDB_ENTRY_NAME)
                  );

            menu_entries_append_enum(info->list, tmp, "",
                  MENU_ENUM_LABEL_CORE_INFO_ENTRY,
                  MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
         }
      }
   }

   if (core_info->notes)
   {
      for (i = 0; i < core_info->note_list->size; i++)
      {
         strlcpy(tmp,
               core_info->note_list->elems[i].data, sizeof(tmp));
         menu_entries_append_enum(info->list, tmp, "",
               MENU_ENUM_LABEL_CORE_INFO_ENTRY, MENU_SETTINGS_CORE_INFO_NONE, 0, 0);
      }
   }

#if defined(__WINRT__) || defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#else
  if (settings->bools.menu_show_core_updater)
     menu_entries_append_enum(info->list,
           msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_DELETE),
           msg_hash_to_str(MENU_ENUM_LABEL_CORE_DELETE),
           MENU_ENUM_LABEL_CORE_DELETE,
           MENU_SETTING_ACTION_CORE_DELETE, 0, 0);
#endif

   return 0;
}