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
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
#define  MENU_ENUM_LABEL_RDB_ENTRY_BBFC_RATING 143 
#define  MENU_ENUM_LABEL_RDB_ENTRY_CERO_RATING 142 
#define  MENU_ENUM_LABEL_RDB_ENTRY_DEVELOPER 141 
#define  MENU_ENUM_LABEL_RDB_ENTRY_EDGE_MAGAZINE_ISSUE 140 
#define  MENU_ENUM_LABEL_RDB_ENTRY_EDGE_MAGAZINE_RATING 139 
#define  MENU_ENUM_LABEL_RDB_ENTRY_ELSPA_RATING 138 
#define  MENU_ENUM_LABEL_RDB_ENTRY_ENHANCEMENT_HW 137 
#define  MENU_ENUM_LABEL_RDB_ENTRY_ESRB_RATING 136 
#define  MENU_ENUM_LABEL_RDB_ENTRY_FAMITSU_MAGAZINE_RATING 135 
#define  MENU_ENUM_LABEL_RDB_ENTRY_FRANCHISE 134 
#define  MENU_ENUM_LABEL_RDB_ENTRY_MAX_USERS 133 
#define  MENU_ENUM_LABEL_RDB_ENTRY_ORIGIN 132 
#define  MENU_ENUM_LABEL_RDB_ENTRY_PEGI_RATING 131 
#define  MENU_ENUM_LABEL_RDB_ENTRY_PUBLISHER 130 
#define  MENU_ENUM_LABEL_RDB_ENTRY_RELEASE_MONTH 129 
#define  MENU_ENUM_LABEL_RDB_ENTRY_RELEASE_YEAR 128 

__attribute__((used)) static int is_rdb_entry(enum msg_hash_enums enum_idx)
{
   switch (enum_idx)
   {
      case MENU_ENUM_LABEL_RDB_ENTRY_PUBLISHER:
      case MENU_ENUM_LABEL_RDB_ENTRY_DEVELOPER:
      case MENU_ENUM_LABEL_RDB_ENTRY_ORIGIN:
      case MENU_ENUM_LABEL_RDB_ENTRY_FRANCHISE:
      case MENU_ENUM_LABEL_RDB_ENTRY_ENHANCEMENT_HW:
      case MENU_ENUM_LABEL_RDB_ENTRY_ESRB_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_BBFC_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_ELSPA_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_PEGI_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_CERO_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_EDGE_MAGAZINE_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_EDGE_MAGAZINE_ISSUE:
      case MENU_ENUM_LABEL_RDB_ENTRY_FAMITSU_MAGAZINE_RATING:
      case MENU_ENUM_LABEL_RDB_ENTRY_RELEASE_MONTH:
      case MENU_ENUM_LABEL_RDB_ENTRY_RELEASE_YEAR:
      case MENU_ENUM_LABEL_RDB_ENTRY_MAX_USERS:
         break;
      default:
         return -1;
   }

   return 0;
}