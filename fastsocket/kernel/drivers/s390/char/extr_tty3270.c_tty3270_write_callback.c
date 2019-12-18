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
struct tty3270 {int /*<<< orphan*/  write; int /*<<< orphan*/  update_flags; } ;
struct raw3270_request {scalar_t__ rc; scalar_t__ view; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_UPDATE_ALL ; 
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct raw3270_request*) ; 

__attribute__((used)) static void
tty3270_write_callback(struct raw3270_request *rq, void *data)
{
	struct tty3270 *tp;

	tp = (struct tty3270 *) rq->view;
	if (rq->rc != 0) {
		/* Write wasn't successfull. Refresh all. */
		tp->update_flags = TTY_UPDATE_ALL;
		tty3270_set_timer(tp, 1);
	}
	raw3270_request_reset(rq);
	xchg(&tp->write, rq);
}