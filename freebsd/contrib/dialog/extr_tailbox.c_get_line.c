#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tab_len; } ;
struct TYPE_8__ {scalar_t__ tab_correct; } ;
struct TYPE_6__ {int /*<<< orphan*/ * input; } ;
struct TYPE_7__ {int hscroll; char* line; TYPE_1__ obj; } ;
typedef  TYPE_2__ MY_OBJ ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MAX_LEN ; 
 int TAB ; 
 TYPE_5__ dialog_state ; 
 TYPE_4__ dialog_vars ; 
 int /*<<< orphan*/  dlg_exiterr (char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
get_line(MY_OBJ * obj)
{
    FILE *fp = obj->obj.input;
    int col = -(obj->hscroll);
    int j, tmpint, ch;

    do {
	if (((ch = getc(fp)) == EOF) && !feof(fp))
	    dlg_exiterr("Error moving file pointer in get_line().");
	else if (!feof(fp) && (ch != '\n')) {
	    if ((ch == TAB) && (dialog_vars.tab_correct)) {
		tmpint = dialog_state.tab_len
		    - ((col + obj->hscroll) % dialog_state.tab_len);
		for (j = 0; j < tmpint; j++) {
		    if (col >= 0 && col < MAX_LEN)
			obj->line[col] = ' ';
		    ++col;
		}
	    } else {
		if (col >= 0)
		    obj->line[col] = (char) ch;
		++col;
	    }
	    if (col >= MAX_LEN)
		break;
	}
    } while (!feof(fp) && (ch != '\n'));

    if (col < 0)
	col = 0;
    obj->line[col] = '\0';

    return obj->line;
}