#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int finish_string; } ;
struct TYPE_4__ {int percent; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 TYPE_3__ dialog_state ; 
 int /*<<< orphan*/  repaint_text (TYPE_1__*) ; 

void
dlg_update_gauge(void *objptr, int percent)
{
    MY_OBJ *obj = (MY_OBJ *) objptr;
    bool save_finish_string = dialog_state.finish_string;

    dialog_state.finish_string = TRUE;
    curs_set(0);
    obj->percent = percent;
    repaint_text(obj);
    dialog_state.finish_string = save_finish_string;
}