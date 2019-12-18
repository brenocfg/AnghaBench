#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  win; } ;
struct TYPE_5__ {TYPE_1__ obj; int /*<<< orphan*/  old_wide; int /*<<< orphan*/  wide; int /*<<< orphan*/  old_high; int /*<<< orphan*/  high; int /*<<< orphan*/  prompt; } ;
typedef  TYPE_2__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
restart_obj(MY_OBJ * obj)
{
    free(obj->prompt);
    obj->high = obj->old_high;
    obj->wide = obj->old_wide;
    dlg_clear();
    dlg_del_window(obj->obj.win);
}