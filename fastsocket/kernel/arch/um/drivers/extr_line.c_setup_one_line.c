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
struct line {int init_pri; int valid; char* init_str; int /*<<< orphan*/  count_lock; int /*<<< orphan*/ * tty; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int setup_one_line(struct line *lines, int n, char *init, int init_prio,
			  char **error_out)
{
	struct line *line = &lines[n];
	int err = -EINVAL;

	spin_lock(&line->count_lock);

	if (line->tty != NULL) {
		*error_out = "Device is already open";
		goto out;
	}

	if (line->init_pri <= init_prio) {
		line->init_pri = init_prio;
		if (!strcmp(init, "none"))
			line->valid = 0;
		else {
			line->init_str = init;
			line->valid = 1;
		}
	}
	err = 0;
out:
	spin_unlock(&line->count_lock);
	return err;
}