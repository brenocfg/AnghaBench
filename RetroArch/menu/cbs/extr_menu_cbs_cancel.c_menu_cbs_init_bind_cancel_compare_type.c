#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_CANCEL (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  FILE_TYPE_DOWNLOAD_CORE 155 
#define  FILE_TYPE_DOWNLOAD_CORE_CONTENT 154 
#define  FILE_TYPE_DOWNLOAD_URL 153 
#define  MENU_ENUM_LABEL_CHEAT_ADDRESS 152 
#define  MENU_ENUM_LABEL_CHEAT_ADDRESS_BIT_POSITION 151 
#define  MENU_ENUM_LABEL_CHEAT_ADD_NEW_AFTER 150 
#define  MENU_ENUM_LABEL_CHEAT_ADD_NEW_BEFORE 149 
#define  MENU_ENUM_LABEL_CHEAT_CODE 148 
#define  MENU_ENUM_LABEL_CHEAT_COPY_AFTER 147 
#define  MENU_ENUM_LABEL_CHEAT_COPY_BEFORE 146 
#define  MENU_ENUM_LABEL_CHEAT_DELETE 145 
#define  MENU_ENUM_LABEL_CHEAT_DESC 144 
#define  MENU_ENUM_LABEL_CHEAT_HANDLER 143 
#define  MENU_ENUM_LABEL_CHEAT_IDX 142 
#define  MENU_ENUM_LABEL_CHEAT_MEMORY_SEARCH_SIZE 141 
#define  MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_ADDRESS 140 
#define  MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_VALUE 139 
#define  MENU_ENUM_LABEL_CHEAT_REPEAT_COUNT 138 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_PORT 137 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_PRIMARY_DURATION 136 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_PRIMARY_STRENGTH 135 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_SECONDARY_DURATION 134 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_SECONDARY_STRENGTH 133 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_TYPE 132 
#define  MENU_ENUM_LABEL_CHEAT_RUMBLE_VALUE 131 
#define  MENU_ENUM_LABEL_CHEAT_STATE 130 
#define  MENU_ENUM_LABEL_CHEAT_TYPE 129 
#define  MENU_ENUM_LABEL_CHEAT_VALUE 128 
 int /*<<< orphan*/  action_cancel_cheat_details ; 
 int /*<<< orphan*/  action_cancel_core_content ; 

__attribute__((used)) static int menu_cbs_init_bind_cancel_compare_type(
      menu_file_list_cbs_t *cbs, unsigned type)
{
   switch (type)
   {
      case FILE_TYPE_DOWNLOAD_CORE_CONTENT:
      case FILE_TYPE_DOWNLOAD_URL:
      case FILE_TYPE_DOWNLOAD_CORE:
         BIND_ACTION_CANCEL(cbs, action_cancel_core_content);
         return 0;
   }

   switch (cbs->enum_idx)
   {

      case MENU_ENUM_LABEL_CHEAT_IDX:
      case MENU_ENUM_LABEL_CHEAT_STATE:
      case MENU_ENUM_LABEL_CHEAT_DESC:
      case MENU_ENUM_LABEL_CHEAT_HANDLER:
      case MENU_ENUM_LABEL_CHEAT_CODE:
      case MENU_ENUM_LABEL_CHEAT_MEMORY_SEARCH_SIZE:
      case MENU_ENUM_LABEL_CHEAT_TYPE:
      case MENU_ENUM_LABEL_CHEAT_VALUE:
      case MENU_ENUM_LABEL_CHEAT_ADDRESS:
      case MENU_ENUM_LABEL_CHEAT_ADDRESS_BIT_POSITION:
      case MENU_ENUM_LABEL_CHEAT_REPEAT_COUNT:
      case MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_ADDRESS:
      case MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_VALUE:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_TYPE:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_VALUE:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_PORT:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_PRIMARY_STRENGTH:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_PRIMARY_DURATION:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_SECONDARY_STRENGTH:
      case MENU_ENUM_LABEL_CHEAT_RUMBLE_SECONDARY_DURATION:
      case MENU_ENUM_LABEL_CHEAT_ADD_NEW_AFTER:
      case MENU_ENUM_LABEL_CHEAT_ADD_NEW_BEFORE:
      case MENU_ENUM_LABEL_CHEAT_COPY_AFTER:
      case MENU_ENUM_LABEL_CHEAT_COPY_BEFORE:
      case MENU_ENUM_LABEL_CHEAT_DELETE:
      {
         BIND_ACTION_CANCEL(cbs, action_cancel_cheat_details);
         break ;
      }
      default :
      {
         break ;
      }
   }
   return -1;
}