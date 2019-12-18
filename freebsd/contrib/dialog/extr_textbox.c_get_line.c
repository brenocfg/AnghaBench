#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* buf; size_t in_buf; long file_size; char* line; scalar_t__ end_reached; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 scalar_t__ FALSE ; 
 int MAX_LEN ; 
 scalar_t__ TRUE ; 
 long ftell_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  read_high (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_line(MY_OBJ * obj)
{
    int i = 0;
    long fpos;

    obj->end_reached = FALSE;
    while (obj->buf[obj->in_buf] != '\n') {
	if (obj->buf[obj->in_buf] == '\0') {	/* Either end of file or end of buffer reached */
	    fpos = ftell_obj(obj);

	    if (fpos < obj->file_size) {	/* Not end of file yet */
		/* We've reached end of buffer, but not end of file yet, so
		 * read next part of file into buffer
		 */
		read_high(obj, BUF_SIZE);
		obj->in_buf = 0;
	    } else {
		if (!obj->end_reached)
		    obj->end_reached = TRUE;
		break;
	    }
	} else if (i < MAX_LEN)
	    obj->line[i++] = obj->buf[obj->in_buf++];
	else {
	    if (i == MAX_LEN)	/* Truncate lines longer than MAX_LEN characters */
		obj->line[i++] = '\0';
	    obj->in_buf++;
	}
    }
    if (i <= MAX_LEN)
	obj->line[i] = '\0';
    if (!obj->end_reached)
	obj->in_buf++;		/* move past '\n' */

    return obj->line;
}