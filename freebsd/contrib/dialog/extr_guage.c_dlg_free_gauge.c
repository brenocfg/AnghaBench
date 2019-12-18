#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  keep_win; } ;
struct TYPE_5__ {TYPE_3__ obj; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int /*<<< orphan*/  delink (TYPE_1__*) ; 
 int /*<<< orphan*/  dlg_remove_callback (TYPE_3__*) ; 
 scalar_t__ valid (TYPE_1__*) ; 

void
dlg_free_gauge(void *objptr)
{
    MY_OBJ *obj = (MY_OBJ *) objptr;

    if (valid(obj)) {
	obj->obj.keep_win = FALSE;
	dlg_remove_callback(&(obj->obj));
	delink(obj);
    }
    curs_set(1);
}