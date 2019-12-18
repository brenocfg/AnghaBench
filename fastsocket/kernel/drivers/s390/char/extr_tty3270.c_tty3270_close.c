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
struct tty_struct {int count; int /*<<< orphan*/ * driver_data; } ;
struct tty3270 {int /*<<< orphan*/  view; TYPE_1__* kbd; int /*<<< orphan*/  tty; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_put_view (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tty3270_close(struct tty_struct *tty, struct file * filp)
{
	struct tty3270 *tp;

	if (tty->count > 1)
		return;
	tp = (struct tty3270 *) tty->driver_data;
	if (tp) {
		tty->driver_data = NULL;
		tp->tty = tp->kbd->tty = NULL;
		raw3270_put_view(&tp->view);
	}
}