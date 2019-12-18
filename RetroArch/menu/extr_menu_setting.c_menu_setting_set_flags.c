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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int FILE_TYPE_PATH ; 
 int MENU_SETTING_ACTION ; 
 int MENU_SETTING_GROUP ; 
 int MENU_SETTING_STRING_OPTIONS ; 
 int MENU_SETTING_SUBGROUP ; 
#define  ST_ACTION 132 
#define  ST_GROUP 131 
#define  ST_PATH 130 
#define  ST_STRING_OPTIONS 129 
#define  ST_SUB_GROUP 128 
 int setting_get_type (int /*<<< orphan*/ *) ; 

int menu_setting_set_flags(rarch_setting_t *setting)
{
   if (!setting)
      return 0;

   switch (setting_get_type(setting))
   {
      case ST_STRING_OPTIONS:
         return MENU_SETTING_STRING_OPTIONS;
      case ST_ACTION:
         return MENU_SETTING_ACTION;
      case ST_PATH:
         return FILE_TYPE_PATH;
      case ST_GROUP:
         return MENU_SETTING_GROUP;
      case ST_SUB_GROUP:
         return MENU_SETTING_SUBGROUP;
      default:
         break;
   }

   return 0;
}