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
struct tty_struct {int count; struct line* driver_data; } ;
struct line {int /*<<< orphan*/  count_lock; scalar_t__ sigio; int /*<<< orphan*/ * tty; int /*<<< orphan*/  valid; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_buffer (struct line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_winch (struct tty_struct*) ; 

void line_close(struct tty_struct *tty, struct file * filp)
{
	struct line *line = tty->driver_data;

	/*
	 * If line_open fails (and tty->driver_data is never set),
	 * tty_open will call line_close.  So just return in this case.
	 */
	if (line == NULL)
		return;

	/* We ignore the error anyway! */
	flush_buffer(line);

	spin_lock(&line->count_lock);
	if (!line->valid)
		goto out_unlock;

	if (tty->count > 1)
		goto out_unlock;

	spin_unlock(&line->count_lock);

	line->tty = NULL;
	tty->driver_data = NULL;

	if (line->sigio) {
		unregister_winch(tty);
		line->sigio = 0;
	}

	return;

out_unlock:
	spin_unlock(&line->count_lock);
}