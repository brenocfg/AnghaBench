#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  keep_win; scalar_t__ input; scalar_t__ caller; int /*<<< orphan*/  win; } ;
struct TYPE_7__ {int percent; TYPE_3__ obj; } ;
typedef  TYPE_1__ MY_OBJ ;
typedef  int /*<<< orphan*/  DIALOG_CALLBACK ;

/* Variables and functions */
 int DLG_EXIT_OK ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int /*<<< orphan*/  DLG_TRACE2N (char*,int) ; 
 int /*<<< orphan*/  DLG_TRACE2S (char*,char const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int KEY_RESIZE ; 
 int /*<<< orphan*/  dlg_add_callback_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 void* dlg_allocate_gauge (char const*,char const*,int,int,int) ; 
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_free_gauge (TYPE_1__*) ; 
 int dlg_getc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dlg_mouse_free_regions () ; 
 int /*<<< orphan*/  dlg_remove_callback (TYPE_3__*) ; 
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_update_gauge (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dlg_will_resize (int /*<<< orphan*/ ) ; 
 scalar_t__ handle_my_getc (TYPE_3__*,int,int,int*) ; 
 int /*<<< orphan*/  my_cleanup ; 
 int /*<<< orphan*/  refresh () ; 
 scalar_t__ valid (TYPE_1__*) ; 

int
dialog_gauge(const char *title,
	     const char *cprompt,
	     int height,
	     int width,
	     int percent)
{
    int fkey;
    int ch, result;
    void *objptr = dlg_allocate_gauge(title, cprompt, height, width, percent);
    MY_OBJ *obj = (MY_OBJ *) objptr;

    DLG_TRACE(("# gauge args:\n"));
    DLG_TRACE2S("title", title);
    DLG_TRACE2S("message", cprompt);
    DLG_TRACE2N("height", height);
    DLG_TRACE2N("width", width);
    DLG_TRACE2N("percent", percent);

    dlg_add_callback_ref((DIALOG_CALLBACK **) & obj, my_cleanup);
    dlg_update_gauge(obj, percent);

    dlg_trace_win(obj->obj.win);
    do {
	ch = dlg_getc(obj->obj.win, &fkey);
#ifdef KEY_RESIZE
	if (fkey && ch == KEY_RESIZE) {
	    MY_OBJ *oldobj = obj;

	    dlg_will_resize(obj->obj.win);
	    dlg_mouse_free_regions();

	    obj = dlg_allocate_gauge(title,
				     cprompt,
				     height,
				     width,
				     oldobj->percent);

	    /* avoid breaking new window in dlg_remove_callback */
	    oldobj->obj.caller = 0;
	    oldobj->obj.input = 0;
	    oldobj->obj.keep_win = FALSE;

	    /* remove the old version of the gauge */
	    dlg_clear();
	    dlg_remove_callback(&(oldobj->obj));
	    refresh();

	    dlg_add_callback_ref((DIALOG_CALLBACK **) & obj, my_cleanup);
	    dlg_update_gauge(obj, obj->percent);
	}
#endif
    }
    while (valid(obj) && handle_my_getc(&(obj->obj), ch, fkey, &result));

    dlg_free_gauge(obj);

    return (DLG_EXIT_OK);
}