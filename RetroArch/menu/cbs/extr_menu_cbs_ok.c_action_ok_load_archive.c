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
struct TYPE_3__ {char* scratch2_buf; char* scratch_buf; int /*<<< orphan*/  detect_content_path; } ;
typedef  TYPE_1__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_LOAD_CORE ; 
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int default_action_ok_load_content_with_core_from_menu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int /*<<< orphan*/  generic_action_ok_command (int /*<<< orphan*/ ) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 

__attribute__((used)) static int action_ok_load_archive(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   const char *menu_path           = NULL;
   const char *content_path        = NULL;
   menu_handle_t *menu             = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   menu_path    = menu->scratch2_buf;
   content_path = menu->scratch_buf;

   fill_pathname_join(menu->detect_content_path,
         menu_path, content_path,
         sizeof(menu->detect_content_path));

   generic_action_ok_command(CMD_EVENT_LOAD_CORE);

   return default_action_ok_load_content_with_core_from_menu(
         menu->detect_content_path,
         CORE_TYPE_PLAIN);
}