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
struct tty3270 {int /*<<< orphan*/  update_flags; } ;
struct raw3270_view {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_UPDATE_ALL ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 

__attribute__((used)) static int
tty3270_activate(struct raw3270_view *view)
{
	struct tty3270 *tp;

	tp = (struct tty3270 *) view;
	tp->update_flags = TTY_UPDATE_ALL;
	tty3270_set_timer(tp, 1);
	return 0;
}