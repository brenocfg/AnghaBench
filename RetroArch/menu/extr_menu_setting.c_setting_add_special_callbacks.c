#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/  action_start; void* action_select; void* action_ok; } ;
typedef  TYPE_1__ rarch_setting_t ;
struct TYPE_6__ {int index; } ;
typedef  TYPE_2__ rarch_setting_info_t ;

/* Variables and functions */
 unsigned int SD_FLAG_ALLOW_INPUT ; 
#define  ST_HEX 131 
#define  ST_SIZE 130 
#define  ST_STRING 129 
#define  ST_UINT 128 
 void* setting_generic_action_ok_linefeed ; 
 int /*<<< orphan*/  setting_string_action_start_generic ; 

__attribute__((used)) static void setting_add_special_callbacks(
      rarch_setting_t **list,
      rarch_setting_info_t *list_info,
      unsigned values)
{
   unsigned idx = list_info->index - 1;

   if (values & SD_FLAG_ALLOW_INPUT)
   {
      (*list)[idx].action_ok     = setting_generic_action_ok_linefeed;
      (*list)[idx].action_select = setting_generic_action_ok_linefeed;

      switch ((*list)[idx].type)
      {
         case ST_SIZE:
         case ST_UINT:
            (*list)[idx].action_cancel = NULL;
            break;
         case ST_HEX:
            (*list)[idx].action_cancel = NULL;
            break;
         case ST_STRING:
            (*list)[idx].action_start  = setting_string_action_start_generic;
            (*list)[idx].action_cancel = NULL;
            break;
         default:
            break;
      }
   }
}