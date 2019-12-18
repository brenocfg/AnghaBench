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
struct tty_struct {int index; struct tty_struct* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 

__attribute__((used)) static void release_tty(struct tty_struct *tty, int idx)
{
	/* This should always be true but check for the moment */
	WARN_ON(tty->index != idx);

	if (tty->link)
		tty_kref_put(tty->link);
	tty_kref_put(tty);
}