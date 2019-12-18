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
struct TYPE_4__ {int /*<<< orphan*/ * input; } ;
struct TYPE_5__ {TYPE_1__ obj; } ;
typedef  TYPE_2__ MY_OBJ ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  dlg_exiterr (char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
last_lines(MY_OBJ * obj, int target)
{
    FILE *fp = obj->obj.input;
    size_t inx;
    int count = 0;
    char buf[BUFSIZ + 1];
    size_t size_to_read;
    size_t size_as_read;
    long offset = 0;
    long fpos = 0;

    if (fseek(fp, 0L, SEEK_END) == -1
	|| (fpos = ftell(fp)) < 0)
	dlg_exiterr("Error moving file pointer in last_lines().");

    if (fpos != 0) {
	++target;
	for (;;) {
	    if (fpos >= BUFSIZ) {
		size_to_read = BUFSIZ;
	    } else {
		size_to_read = (size_t) fpos;
	    }
	    fpos = fpos - (long) size_to_read;
	    if (fseek(fp, fpos, SEEK_SET) == -1)
		dlg_exiterr("Error moving file pointer in last_lines().");
	    size_as_read = fread(buf, sizeof(char), size_to_read, fp);
	    if (ferror(fp))
		dlg_exiterr("Error reading file in last_lines().");

	    if (size_as_read == 0) {
		fpos = 0;
		offset = 0;
		break;
	    }

	    offset += (long) size_as_read;
	    for (inx = size_as_read - 1; inx != 0; --inx) {
		if (buf[inx] == '\n') {
		    if (++count > target)
			break;
		    offset = (long) (inx + 1);
		}
	    }

	    if (count > target) {
		break;
	    } else if (fpos == 0) {
		offset = 0;
		break;
	    }
	}

	if (fseek(fp, fpos + offset, SEEK_SET) == -1)
	    dlg_exiterr("Error moving file pointer in last_lines().");
    }
}