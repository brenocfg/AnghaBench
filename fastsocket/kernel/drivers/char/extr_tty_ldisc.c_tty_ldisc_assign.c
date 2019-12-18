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
struct tty_struct {struct tty_ldisc* ldisc; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void tty_ldisc_assign(struct tty_struct *tty, struct tty_ldisc *ld)
{
	tty->ldisc = ld;
}