#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct file_list {scalar_t__ f_type; char* f_fn; struct file_list* f_next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ INVISIBLE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 struct file_list* ftab ; 
 int /*<<< orphan*/  put_source_file_name (int /*<<< orphan*/ *,struct file_list*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

void
do_files(FILE *fp, const char *msg, char ext)
{
	struct file_list *tp;
	int lpos, len=0; /* dvw: init to 0 */

	fprintf(fp, "%s", msg);
	lpos = 8;
	for (tp = ftab; tp != 0; tp = tp->f_next) {
		if (tp->f_type == INVISIBLE)
			continue;
		if (tp->f_fn[strlen(tp->f_fn)-1] != ext)
			continue;
		/*
		 * Always generate a newline.
		 * Our Makefile's aren't readable anyway.
		 */

		lpos = 8;
		fprintf(fp, "\\\n\t");
		put_source_file_name(fp, tp);
		lpos += len + 1;
	}
	putc('\n', fp);
}