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
struct TYPE_3__ {int /*<<< orphan*/  detect_content_path; } ;
typedef  TYPE_1__ menu_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int file_load_with_detect_core_wrapper (int /*<<< orphan*/ ,size_t,size_t,char const*,char const*,unsigned int,int) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char,int) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 

__attribute__((used)) static int action_ok_file_load_with_detect_core_carchive(
      const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   menu_handle_t *menu                 = menu_driver_get_ptr();

   if (!menu)
      return menu_cbs_exit();

   fill_pathname_join_delim(menu->detect_content_path,
         menu->detect_content_path, path,
         '#', sizeof(menu->detect_content_path));

   type = 0;
   label = NULL;

   return file_load_with_detect_core_wrapper(
         MSG_UNKNOWN, idx, entry_idx,
         path, label, type, true);
}