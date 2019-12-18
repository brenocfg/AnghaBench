#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_SELECT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MENU_ENUM_LABEL_CONNECT_NETPLAY_ROOM ; 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 int /*<<< orphan*/  action_select_core_setting ; 
 int /*<<< orphan*/  action_select_default ; 
 int /*<<< orphan*/  action_select_netplay_connect_room ; 
 scalar_t__ menu_cbs_init_bind_select_compare_label (TYPE_1__*,char const*) ; 
 scalar_t__ menu_cbs_init_bind_select_compare_type (TYPE_1__*,unsigned int) ; 

int menu_cbs_init_bind_select(menu_file_list_cbs_t *cbs,
      const char *path, const char *label, unsigned type, size_t idx)
{
   if (!cbs)
      return -1;

   BIND_ACTION_SELECT(cbs, action_select_default);

#ifdef HAVE_NETWORKING
   if (cbs->enum_idx == MENU_ENUM_LABEL_CONNECT_NETPLAY_ROOM)
   {
      BIND_ACTION_SELECT(cbs, action_select_netplay_connect_room);
      return 0;
   }
#endif

   if ((type >= MENU_SETTINGS_CORE_OPTION_START) &&
       (type < MENU_SETTINGS_CHEEVOS_START))
   {
      BIND_ACTION_SELECT(cbs, action_select_core_setting);
      return 0;
   }

   if (menu_cbs_init_bind_select_compare_label(cbs, label) == 0)
      return 0;

   if (menu_cbs_init_bind_select_compare_type(cbs, type) == 0)
      return 0;

   return -1;
}