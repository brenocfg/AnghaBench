#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long tab_len; } ;
struct TYPE_6__ {scalar_t__ tab_correct; } ;
struct TYPE_5__ {int fd_bytes_read; long bytes_read; long buffer_len; char* buf; void* buffer_first; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 void* FALSE ; 
 char TAB ; 
 TYPE_4__ dialog_state ; 
 TYPE_3__ dialog_vars ; 
 int /*<<< orphan*/  dlg_exiterr (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 
 void* xalloc (size_t) ; 

__attribute__((used)) static void
read_high(MY_OBJ * obj, size_t size_read)
{
    char *buftab, ch;
    int i = 0, j, n, tmpint;
    long begin_line;

    /* Allocate space for read buffer */
    buftab = xalloc(size_read + 1);

    if ((obj->fd_bytes_read = read(obj->fd, buftab, size_read)) != -1) {

	buftab[obj->fd_bytes_read] = '\0';	/* mark end of valid data */

	if (dialog_vars.tab_correct) {

	    /* calculate bytes_read by buftab and fd_bytes_read */
	    obj->bytes_read = begin_line = 0;
	    for (j = 0; j < obj->fd_bytes_read; j++)
		if (buftab[j] == TAB)
		    obj->bytes_read += dialog_state.tab_len
			- ((obj->bytes_read - begin_line)
			   % dialog_state.tab_len);
		else if (buftab[j] == '\n') {
		    obj->bytes_read++;
		    begin_line = obj->bytes_read;
		} else
		    obj->bytes_read++;

	    if (obj->bytes_read > obj->buffer_len) {
		if (obj->buffer_first)
		    obj->buffer_first = FALSE;	/* disp = 0 */
		else {
		    free(obj->buf);
		}

		obj->buffer_len = obj->bytes_read;

		/* Allocate space for read buffer */
		obj->buf = xalloc((size_t) obj->buffer_len + 1);
	    }

	} else {
	    if (obj->buffer_first) {
		obj->buffer_first = FALSE;

		/* Allocate space for read buffer */
		obj->buf = xalloc(size_read + 1);
	    }

	    obj->bytes_read = obj->fd_bytes_read;
	}

	j = 0;
	begin_line = 0;
	while (j < obj->fd_bytes_read)
	    if (((ch = buftab[j++]) == TAB) && (dialog_vars.tab_correct != 0)) {
		tmpint = (dialog_state.tab_len
			  - ((int) ((long) i - begin_line) % dialog_state.tab_len));
		for (n = 0; n < tmpint; n++)
		    obj->buf[i++] = ' ';
	    } else {
		if (ch == '\n')
		    begin_line = i + 1;
		obj->buf[i++] = ch;
	    }

	obj->buf[i] = '\0';	/* mark end of valid data */

    }
    if (obj->bytes_read == -1)
	dlg_exiterr("Error reading file");
    free(buftab);
}