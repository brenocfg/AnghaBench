#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;
struct tty_struct {size_t index; int count; TYPE_1__ winsize; struct line* driver_data; } ;
struct line {int sigio; int /*<<< orphan*/  count_lock; int /*<<< orphan*/  chan_list; int /*<<< orphan*/  task; struct tty_struct* tty; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_enable_winch (int /*<<< orphan*/ *,struct tty_struct*) ; 
 int /*<<< orphan*/  chan_window_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int enable_chan (struct line*) ; 
 int /*<<< orphan*/  line_timer_cb ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int line_open(struct line *lines, struct tty_struct *tty)
{
	struct line *line = &lines[tty->index];
	int err = -ENODEV;

	spin_lock(&line->count_lock);
	if (!line->valid)
		goto out_unlock;

	err = 0;
	if (tty->count > 1)
		goto out_unlock;

	spin_unlock(&line->count_lock);

	tty->driver_data = line;
	line->tty = tty;

	err = enable_chan(line);
	if (err)
		return err;

	INIT_DELAYED_WORK(&line->task, line_timer_cb);

	if (!line->sigio) {
		chan_enable_winch(&line->chan_list, tty);
		line->sigio = 1;
	}

	chan_window_size(&line->chan_list, &tty->winsize.ws_row,
			 &tty->winsize.ws_col);

	return err;

out_unlock:
	spin_unlock(&line->count_lock);
	return err;
}