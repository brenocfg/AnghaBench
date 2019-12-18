#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cheevos_test_unofficial; scalar_t__ cheevos_hardcore_mode_enable; scalar_t__ cheevos_enable; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  rcheevos_cheevo_t ;
struct TYPE_11__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_4__ menu_displaylist_info_t ;
struct TYPE_9__ {int core_count; int unofficial_count; } ;
struct TYPE_12__ {TYPE_2__ patchdata; int /*<<< orphan*/ * unofficial; int /*<<< orphan*/ * core; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_NONE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ACHIEVEMENT_PAUSE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ACHIEVEMENT_RESUME ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CHEEVOS_LOCKED_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CHEEVOS_UNOFFICIAL_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NO_ACHIEVEMENTS_TO_DISPLAY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_PAUSE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_RESUME ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NO_ACHIEVEMENTS_TO_DISPLAY ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_PAUSE_ACHIEVEMENTS ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_RESUME_ACHIEVEMENTS ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcheevos_append_menu_achievement (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcheevos_hardcore_paused ; 
 scalar_t__ rcheevos_loaded ; 
 TYPE_5__ rcheevos_locals ; 

void rcheevos_populate_menu(void* data)
{
#ifdef HAVE_MENU
   int i                         = 0;
   int count                     = 0;
   settings_t* settings          = config_get_ptr();
   menu_displaylist_info_t* info = (menu_displaylist_info_t*)data;
   rcheevos_cheevo_t* cheevo      = NULL;

   if (   settings->bools.cheevos_enable
       && settings->bools.cheevos_hardcore_mode_enable
       && rcheevos_loaded)
   {
      if (!rcheevos_hardcore_paused)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_PAUSE),
               msg_hash_to_str(MENU_ENUM_LABEL_ACHIEVEMENT_PAUSE),
               MENU_ENUM_LABEL_ACHIEVEMENT_PAUSE,
               MENU_SETTING_ACTION_PAUSE_ACHIEVEMENTS, 0, 0);
      else
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_RESUME),
               msg_hash_to_str(MENU_ENUM_LABEL_ACHIEVEMENT_RESUME),
               MENU_ENUM_LABEL_ACHIEVEMENT_RESUME,
               MENU_SETTING_ACTION_RESUME_ACHIEVEMENTS, 0, 0);
   }

   cheevo = rcheevos_locals.core;
   for (count = rcheevos_locals.patchdata.core_count; count > 0; count--)
   {
      rcheevos_append_menu_achievement(info, i++, MENU_ENUM_LABEL_CHEEVOS_LOCKED_ENTRY, cheevo++);
   }

   if (settings->bools.cheevos_test_unofficial)
   {
      cheevo = rcheevos_locals.unofficial;
      for (count = rcheevos_locals.patchdata.unofficial_count; count > 0; count--)
      {
         rcheevos_append_menu_achievement(info, i++, MENU_ENUM_LABEL_CHEEVOS_UNOFFICIAL_ENTRY, cheevo++);
      }
   }

   if (i == 0)
   {
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_ACHIEVEMENTS_TO_DISPLAY),
            msg_hash_to_str(MENU_ENUM_LABEL_NO_ACHIEVEMENTS_TO_DISPLAY),
            MENU_ENUM_LABEL_NO_ACHIEVEMENTS_TO_DISPLAY,
            FILE_TYPE_NONE, 0, 0);
   }
#endif
}