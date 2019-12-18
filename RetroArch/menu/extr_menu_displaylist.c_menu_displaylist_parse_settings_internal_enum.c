#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int menu_show_advanced_settings; } ;
struct TYPE_9__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_10__ {int flags; char* short_description; char* name; } ;
typedef  TYPE_3__ rarch_setting_t ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum setting_type { ____Placeholder_setting_type } setting_type ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  enum menu_displaylist_parse_type { ____Placeholder_menu_displaylist_parse_type } menu_displaylist_parse_type ;

/* Variables and functions */
 int MENU_ENUM_LABEL_NO_SETTINGS_FOUND ; 
 int MENU_ENUM_LABEL_VALUE_NO_SETTINGS_FOUND ; 
 unsigned int MENU_SETTINGS_INPUT_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_END ; 
#define  PARSE_ACTION 160 
#define  PARSE_GROUP 159 
#define  PARSE_NONE 158 
#define  PARSE_ONLY_BIND 157 
#define  PARSE_ONLY_BOOL 156 
#define  PARSE_ONLY_DIR 155 
#define  PARSE_ONLY_FLOAT 154 
#define  PARSE_ONLY_GROUP 153 
#define  PARSE_ONLY_HEX 152 
#define  PARSE_ONLY_INT 151 
#define  PARSE_ONLY_PATH 150 
#define  PARSE_ONLY_SIZE 149 
#define  PARSE_ONLY_STRING 148 
#define  PARSE_ONLY_STRING_OPTIONS 147 
#define  PARSE_ONLY_UINT 146 
#define  PARSE_SUB_GROUP 145 
 int SD_FLAG_ADVANCED ; 
 int SD_FLAG_LAKKA_ADVANCED ; 
#define  ST_ACTION 144 
#define  ST_BIND 143 
#define  ST_BOOL 142 
#define  ST_DIR 141 
#define  ST_END_GROUP 140 
#define  ST_END_SUB_GROUP 139 
#define  ST_FLOAT 138 
#define  ST_GROUP 137 
#define  ST_HEX 136 
#define  ST_INT 135 
#define  ST_NONE 134 
#define  ST_PATH 133 
#define  ST_SIZE 132 
#define  ST_STRING 131 
#define  ST_STRING_OPTIONS 130 
#define  ST_SUB_GROUP 129 
#define  ST_UINT 128 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_append (int /*<<< orphan*/ *,char const*,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ *,char const*,char const*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int menu_setting_set_flags (TYPE_3__*) ; 
 char const* msg_hash_to_str (int) ; 
 int setting_get_type (TYPE_3__*) ; 

__attribute__((used)) static int menu_displaylist_parse_settings_internal_enum(
      file_list_t *info_list,
      enum menu_displaylist_parse_type parse_type,
      bool add_empty_entry,
      rarch_setting_t *setting,
      unsigned entry_type,
      bool is_enum
      )
{
   static enum setting_type precond_lut[] =
   {
      ST_END_GROUP,              /* PARSE_NONE                */
      ST_NONE,                   /* PARSE_GROUP               */
      ST_ACTION,                 /* PARSE_ACTION              */
      ST_INT,                    /* PARSE_ONLY_INT            */
      ST_UINT,                   /* PARSE_ONLY_UINT           */
      ST_BOOL,                   /* PARSE_ONLY_BOOL           */
      ST_FLOAT,                  /* PARSE_ONLY_FLOAT          */
      ST_BIND,                   /* PARSE_ONLY_BIND           */
      ST_END_GROUP,              /* PARSE_ONLY_GROUP          */
      ST_STRING,                 /* PARSE_ONLY_STRING         */
      ST_PATH,                   /* PARSE_ONLY_PATH           */
      ST_STRING_OPTIONS,         /* PARSE_ONLY_STRING_OPTIONS */
      ST_HEX,                    /* PARSE_ONLY_HEX            */
      ST_DIR,                    /* PARSE_ONLY_DIR            */
      ST_NONE,                   /* PARSE_SUB_GROUP           */
      ST_SIZE,                   /* PARSE_ONLY_SIZE           */
   };
   enum setting_type precond   = precond_lut[parse_type];
   size_t             count    = 0;
   settings_t *settings        = config_get_ptr();
   bool show_advanced_settings = settings->bools.menu_show_advanced_settings;

   if (!setting)
      return -1;

   if (!show_advanced_settings)
   {
      uint64_t flags = setting->flags;
      if (flags & SD_FLAG_ADVANCED)
         goto end;
#ifdef HAVE_LAKKA
      if (flags & SD_FLAG_LAKKA_ADVANCED)
         goto end;
#endif
   }

   for (;;)
   {
      bool time_to_exit             = false;
      const char *short_description = setting->short_description;
      const char *name              = setting->name;
      enum setting_type type        = setting_get_type(setting);
      rarch_setting_t **list        = &setting;

      switch (parse_type)
      {
         case PARSE_NONE:
            switch (type)
            {
               case ST_GROUP:
               case ST_END_GROUP:
               case ST_SUB_GROUP:
               case ST_END_SUB_GROUP:
                  goto loop;
               default:
                  break;
            }
            break;
         case PARSE_GROUP:
         case PARSE_ONLY_GROUP:
            if (type == ST_GROUP)
               break;
            goto loop;
         case PARSE_SUB_GROUP:
            break;
         case PARSE_ACTION:
         case PARSE_ONLY_INT:
         case PARSE_ONLY_UINT:
         case PARSE_ONLY_SIZE:
         case PARSE_ONLY_BIND:
         case PARSE_ONLY_BOOL:
         case PARSE_ONLY_FLOAT:
         case PARSE_ONLY_HEX:
         case PARSE_ONLY_STRING:
         case PARSE_ONLY_PATH:
         case PARSE_ONLY_DIR:
         case PARSE_ONLY_STRING_OPTIONS:
            if (type == precond)
               break;
            goto loop;
      }

      if (is_enum)
         menu_entries_append_enum(info_list,
               short_description, name,
               (enum msg_hash_enums)entry_type,
               menu_setting_set_flags(setting), 0, 0);
      else
      {
         if (
               (entry_type >= MENU_SETTINGS_INPUT_BEGIN) &&
               (entry_type < MENU_SETTINGS_INPUT_END)
            )
            entry_type = (unsigned)(MENU_SETTINGS_INPUT_BEGIN + count);
         if (entry_type == 0)
            entry_type = menu_setting_set_flags(setting);

         menu_entries_append(info_list, short_description,
               name, entry_type, 0, 0);
      }
      count++;

loop:
      switch (parse_type)
      {
         case PARSE_NONE:
         case PARSE_GROUP:
         case PARSE_ONLY_GROUP:
         case PARSE_SUB_GROUP:
            if (setting_get_type(setting) == precond)
               time_to_exit = true;
            break;
         case PARSE_ONLY_BIND:
         case PARSE_ONLY_FLOAT:
         case PARSE_ONLY_HEX:
         case PARSE_ONLY_BOOL:
         case PARSE_ONLY_INT:
         case PARSE_ONLY_UINT:
         case PARSE_ONLY_SIZE:
         case PARSE_ONLY_PATH:
         case PARSE_ONLY_DIR:
         case PARSE_ONLY_STRING:
         case PARSE_ONLY_STRING_OPTIONS:
         case PARSE_ACTION:
            time_to_exit = true;
            break;
      }

      if (time_to_exit)
         break;
      (*list = *list + 1);
   }

end:
   if (count == 0)
   {
      if (add_empty_entry)
         menu_entries_append_enum(info_list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_SETTINGS_FOUND),
               msg_hash_to_str(MENU_ENUM_LABEL_NO_SETTINGS_FOUND),
               MENU_ENUM_LABEL_NO_SETTINGS_FOUND,
               0, 0, 0);
      return -1;
   }

   return 0;
}