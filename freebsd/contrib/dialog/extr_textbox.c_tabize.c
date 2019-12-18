#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {long tab_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  tab_correct; } ;
struct TYPE_8__ {long fd_bytes_read; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 char TAB ; 
 TYPE_7__ dialog_state ; 
 TYPE_6__ dialog_vars ; 
 int /*<<< orphan*/  dlg_exiterr (char*) ; 
 long find_first (TYPE_1__*,char*,long) ; 
 int /*<<< orphan*/  free (char*) ; 
 long ftell_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  lseek_set (TYPE_1__*,long) ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 
 char* xalloc (size_t) ; 

__attribute__((used)) static long
tabize(MY_OBJ * obj, long val, long *first_pos)
{
    long fpos;
    long i, count, begin_line;
    char *buftab;

    if (!dialog_vars.tab_correct)
	return val;

    fpos = ftell_obj(obj);

    lseek_set(obj, fpos - obj->fd_bytes_read);

    /* Allocate space for read buffer */
    buftab = xalloc((size_t) val + 1);

    if ((read(obj->fd, buftab, (size_t) val)) == -1)
	dlg_exiterr("Error reading file in tabize().");

    begin_line = count = 0;
    if (first_pos != 0)
	*first_pos = 0;

    for (i = 0; i < val; i++) {
	if ((first_pos != 0) && (count >= val)) {
	    *first_pos = find_first(obj, buftab, i);
	    break;
	}
	if (buftab[i] == TAB)
	    count += dialog_state.tab_len
		- ((count - begin_line) % dialog_state.tab_len);
	else if (buftab[i] == '\n') {
	    count++;
	    begin_line = count;
	} else
	    count++;
    }

    lseek_set(obj, fpos);
    free(buftab);
    return count;
}