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
struct string_list {int dummy; } ;
typedef  int /*<<< orphan*/  path_change_data_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* watch_path_for_changes ) (struct string_list*,int,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_1__* frontend_get_ptr () ; 
 int /*<<< orphan*/  stub1 (struct string_list*,int,int /*<<< orphan*/ **) ; 

void frontend_driver_watch_path_for_changes(struct string_list *list, int flags, path_change_data_t **change_data)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();
   if (!frontend || !frontend->watch_path_for_changes)
      return;
   frontend->watch_path_for_changes(list, flags, change_data);
}