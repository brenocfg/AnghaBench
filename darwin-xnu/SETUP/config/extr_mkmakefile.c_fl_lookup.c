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
struct file_list {int /*<<< orphan*/  f_fn; struct file_list* f_next; } ;

/* Variables and functions */
 scalar_t__ eq (int /*<<< orphan*/ ,char*) ; 
 struct file_list* ftab ; 

struct file_list *
fl_lookup(char *file)
{
	struct file_list *fp;

	for (fp = ftab ; fp != 0; fp = fp->f_next) {
		if (eq(fp->f_fn, file))
			return (fp);
	}
	return (0);
}