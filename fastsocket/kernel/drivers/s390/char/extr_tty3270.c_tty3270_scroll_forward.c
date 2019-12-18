#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rows; int /*<<< orphan*/  lock; } ;
struct tty3270 {int nr_up; TYPE_2__ view; } ;
struct kbd_data {TYPE_1__* tty; } ;
struct TYPE_3__ {struct tty3270* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty3270_rebuild_update (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_update_status (struct tty3270*) ; 

__attribute__((used)) static void
tty3270_scroll_forward(struct kbd_data *kbd)
{
	struct tty3270 *tp;
	int nr_up;

	tp = kbd->tty->driver_data;
	spin_lock_bh(&tp->view.lock);
	nr_up = tp->nr_up - tp->view.rows + 2;
	if (nr_up < 0)
		nr_up = 0;
	if (nr_up != tp->nr_up) {
		tp->nr_up = nr_up;
		tty3270_rebuild_update(tp);
		tty3270_update_status(tp);
		tty3270_set_timer(tp, 1);
	}
	spin_unlock_bh(&tp->view.lock);
}