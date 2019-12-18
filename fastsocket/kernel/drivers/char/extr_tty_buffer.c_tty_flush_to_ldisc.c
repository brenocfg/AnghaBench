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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct tty_struct {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 

void tty_flush_to_ldisc(struct tty_struct *tty)
{
	flush_delayed_work(&tty->buf.work);
}