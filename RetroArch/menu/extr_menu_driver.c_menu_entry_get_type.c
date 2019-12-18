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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_6__ {int /*<<< orphan*/ * setting; } ;
typedef  TYPE_2__ menu_file_list_cbs_t ;
struct TYPE_7__ {TYPE_1__* list; } ;
typedef  TYPE_3__ file_list_t ;
typedef  enum menu_entry_type { ____Placeholder_menu_entry_type } menu_entry_type ;
struct TYPE_5__ {scalar_t__ actiondata; } ;

/* Variables and functions */
 int MENU_ENTRY_ACTION ; 
 int MENU_ENTRY_BIND ; 
 int MENU_ENTRY_BOOL ; 
 int MENU_ENTRY_DIR ; 
 int MENU_ENTRY_ENUM ; 
 int MENU_ENTRY_FLOAT ; 
 int MENU_ENTRY_HEX ; 
 int MENU_ENTRY_INT ; 
 int MENU_ENTRY_PATH ; 
 int MENU_ENTRY_SIZE ; 
 int MENU_ENTRY_STRING ; 
 int MENU_ENTRY_UINT ; 
 int /*<<< orphan*/  MENU_SETTING_CTL_IS_OF_PATH_TYPE ; 
#define  ST_BIND 138 
#define  ST_BOOL 137 
#define  ST_DIR 136 
#define  ST_FLOAT 135 
#define  ST_HEX 134 
#define  ST_INT 133 
#define  ST_PATH 132 
#define  ST_SIZE 131 
#define  ST_STRING 130 
#define  ST_STRING_OPTIONS 129 
#define  ST_UINT 128 
 TYPE_3__* menu_entries_get_selection_buf_ptr_internal (int /*<<< orphan*/ ) ; 
 scalar_t__ menu_setting_ctl (int /*<<< orphan*/ ,void*) ; 
 int setting_get_type (int /*<<< orphan*/ *) ; 

enum menu_entry_type menu_entry_get_type(uint32_t i)
{
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr_internal(0);
   menu_file_list_cbs_t *cbs  = NULL;
   rarch_setting_t *setting   = NULL;
   
   /* FIXME/TODO - XXX Really a special kind of ST_ACTION, 
    * but this should be changed */
   if (menu_setting_ctl(MENU_SETTING_CTL_IS_OF_PATH_TYPE, (void*)setting))
      return MENU_ENTRY_PATH;

   cbs                        = selection_buf ?
      (menu_file_list_cbs_t*)selection_buf->list[i].actiondata : NULL;
   setting                    = cbs ? cbs->setting : NULL;

   if (setting)
   {
      switch (setting_get_type(setting))
      {
         case ST_BOOL:
            return MENU_ENTRY_BOOL;
         case ST_BIND:
            return MENU_ENTRY_BIND;
         case ST_INT:
            return MENU_ENTRY_INT;
         case ST_UINT:
            return MENU_ENTRY_UINT;
         case ST_SIZE:
            return MENU_ENTRY_SIZE;
         case ST_FLOAT:
            return MENU_ENTRY_FLOAT;
         case ST_PATH:
            return MENU_ENTRY_PATH;
         case ST_DIR:
            return MENU_ENTRY_DIR;
         case ST_STRING_OPTIONS:
            return MENU_ENTRY_ENUM;
         case ST_STRING:
            return MENU_ENTRY_STRING;
         case ST_HEX:
            return MENU_ENTRY_HEX;

         default:
            break;
      }
   }

   return MENU_ENTRY_ACTION;
}