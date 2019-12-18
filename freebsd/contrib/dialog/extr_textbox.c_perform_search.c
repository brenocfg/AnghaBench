#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int end_reached; int begin_reached; long page_length; long in_buf; long fd_bytes_read; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 int DLG_EXIT_CANCEL ; 
 int DLG_EXIT_OK ; 
 int FALSE ; 
 int KEY_RESIZE ; 
 int /*<<< orphan*/  PAGE_LENGTH ; 
 int /*<<< orphan*/  PAGE_WIDTH ; 
 int TRUE ; 
 int /*<<< orphan*/  back_lines (TYPE_1__*,long) ; 
 int /*<<< orphan*/  beep () ; 
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell_obj (TYPE_1__*) ; 
 int get_search_term (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek_set (TYPE_1__*,long) ; 
 int match_string (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  read_high (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ungetch (int) ; 

__attribute__((used)) static bool
perform_search(MY_OBJ * obj, int height, int width, int key, char *search_term)
{
    int dir;
    long tempinx;
    long fpos;
    int result;
    bool found;
    bool temp, temp1;
    bool moved = FALSE;

    /* set search direction */
    dir = (key == '/' || key == 'n') ? 1 : 0;
    if (dir ? !obj->end_reached : !obj->begin_reached) {
	if (key == 'n' || key == 'N') {
	    if (search_term[0] == '\0') {	/* No search term yet */
		(void) beep();
		return FALSE;
	    }
	    /* Get search term from user */
	} else if ((result = get_search_term(obj->text, search_term,
					     PAGE_LENGTH,
					     PAGE_WIDTH)) != DLG_EXIT_OK
		   || search_term[0] == '\0') {
#ifdef KEY_RESIZE
	    if (result == DLG_EXIT_CANCEL) {
		ungetch(key);
		ungetch(KEY_RESIZE);
		/* FALLTHRU */
	    }
#endif
	    /* ESC pressed, or no search term, reprint page to clear box */
	    dlg_attrset(obj->text, dialog_attr);
	    back_lines(obj, obj->page_length);
	    return TRUE;
	}
	/* Save variables for restoring in case search term can't be found */
	tempinx = obj->in_buf;
	temp = obj->begin_reached;
	temp1 = obj->end_reached;
	fpos = ftell_obj(obj) - obj->fd_bytes_read;
	/* update 'in_buf' to point to next (previous) line before
	   forward (backward) searching */
	back_lines(obj, (dir
			 ? obj->page_length - 1
			 : obj->page_length + 1));
	if (dir) {		/* Forward search */
	    while ((found = match_string(obj, search_term)) == FALSE) {
		if (obj->end_reached)
		    break;
	    }
	} else {		/* Backward search */
	    while ((found = match_string(obj, search_term)) == FALSE) {
		if (obj->begin_reached)
		    break;
		back_lines(obj, 2L);
	    }
	}
	if (found == FALSE) {	/* not found */
	    (void) beep();
	    /* Restore program state to that before searching */
	    lseek_set(obj, fpos);

	    read_high(obj, BUF_SIZE);

	    obj->in_buf = tempinx;
	    obj->begin_reached = temp;
	    obj->end_reached = temp1;
	    /* move 'in_buf' to point to start of current page to
	     * re-print current page.  Note that 'in_buf' always points
	     * to start of next page, so this is necessary
	     */
	    back_lines(obj, obj->page_length);
	} else {		/* Search term found */
	    back_lines(obj, 1L);
	}
	/* Reprint page */
	dlg_attrset(obj->text, dialog_attr);
	moved = TRUE;
    } else {			/* no need to find */
	(void) beep();
    }
    return moved;
}