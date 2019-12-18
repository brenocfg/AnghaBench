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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
 unsigned int MENU_SETTINGS_NETPLAY_ROOMS_START ; 
 int /*<<< orphan*/  action_info_cheevos ; 
 int /*<<< orphan*/  action_info_default ; 

int menu_cbs_init_bind_info(menu_file_list_cbs_t *cbs,
      const char *path, const char *label, unsigned type, size_t idx)
{
   if (!cbs)
      return -1;

#ifdef HAVE_CHEEVOS
   if ((type >= MENU_SETTINGS_CHEEVOS_START) &&
      (type < MENU_SETTINGS_NETPLAY_ROOMS_START))
   {
      BIND_ACTION_INFO(cbs, action_info_cheevos);
      return 0;
   }
#endif

   BIND_ACTION_INFO(cbs, action_info_default);

   return -1;
}