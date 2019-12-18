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
struct TYPE_5__ {int /*<<< orphan*/  deferred_path; } ;
typedef  TYPE_1__ menu_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/ * environ_get; int /*<<< orphan*/ * args; int /*<<< orphan*/ * argv; scalar_t__ argc; } ;
typedef  TYPE_2__ content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  content_add_to_playlist (char const*) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  task_push_load_content_with_new_core_from_menu (char const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_load_core_deferred(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   content_ctx_info_t content_info;
   menu_handle_t *menu                 = menu_driver_get_ptr();

   content_info.argc                   = 0;
   content_info.argv                   = NULL;
   content_info.args                   = NULL;
   content_info.environ_get            = NULL;

   if (!menu)
      return menu_cbs_exit();

   if (!task_push_load_content_with_new_core_from_menu(
            path, menu->deferred_path,
            &content_info,
            CORE_TYPE_PLAIN,
            NULL, NULL))
      return -1;
   content_add_to_playlist(path);

   return 0;
}