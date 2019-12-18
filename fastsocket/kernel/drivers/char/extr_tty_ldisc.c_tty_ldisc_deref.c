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
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_ldisc (struct tty_ldisc*) ; 

void tty_ldisc_deref(struct tty_ldisc *ld)
{
	put_ldisc(ld);
}