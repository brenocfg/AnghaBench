#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int enum_idx; int /*<<< orphan*/  action_deferred_push; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
#define  MENU_ENUM_LABEL_CONTENT_ACTIONS 128 
 int MSG_UNKNOWN ; 
 int /*<<< orphan*/  xmb_deferred_push_content_actions ; 

__attribute__((used)) static int xmb_list_bind_init_compare_label(menu_file_list_cbs_t *cbs)
{
   if (cbs && cbs->enum_idx != MSG_UNKNOWN)
   {
      switch (cbs->enum_idx)
      {
         case MENU_ENUM_LABEL_CONTENT_ACTIONS:
            cbs->action_deferred_push = xmb_deferred_push_content_actions;
            break;
         default:
            return -1;
      }
   }

   return 0;
}