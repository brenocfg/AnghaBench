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
struct TYPE_3__ {int need_sort; int need_refresh; int need_entries_refresh; int need_push_no_playlist_entries; int need_push; int need_clear; int push_builtin_cores; int download_core; int need_navigation_clear; int /*<<< orphan*/ * setting; int /*<<< orphan*/ * menu_list; int /*<<< orphan*/ * list; int /*<<< orphan*/ * exts; int /*<<< orphan*/ * path_c; int /*<<< orphan*/ * path_b; int /*<<< orphan*/ * path; int /*<<< orphan*/ * label; scalar_t__ directory_ptr; scalar_t__ flags; scalar_t__ type_default; scalar_t__ type; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_1__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_UNKNOWN ; 

void menu_displaylist_info_init(menu_displaylist_info_t *info)
{
   if (!info)
      return;

   info->enum_idx                 = MSG_UNKNOWN;
   info->need_sort                = false;
   info->need_refresh             = false;
   info->need_entries_refresh     = false;
   info->need_push_no_playlist_entries = false;
   info->need_push                = false;
   info->need_clear               = false;
   info->push_builtin_cores       = false;
   info->download_core            = false;
   info->need_navigation_clear    = false;
   info->type                     = 0;
   info->type_default             = 0;
   info->flags                    = 0;
   info->directory_ptr            = 0;
   info->label                    = NULL;
   info->path                     = NULL;
   info->path_b                   = NULL;
   info->path_c                   = NULL;
   info->exts                     = NULL;
   info->list                     = NULL;
   info->menu_list                = NULL;
   info->setting                  = NULL;
}