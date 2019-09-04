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
struct file_list {char* f_fn; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 

void
put_source_file_name(FILE *fp, struct file_list *tp)
{
	if ((tp->f_fn[0] == '.') && (tp->f_fn[1] == '/'))
		fprintf(fp, "%s ", tp->f_fn);
	 else
		fprintf(fp, "$(SOURCE_DIR)/%s ", tp->f_fn);
}