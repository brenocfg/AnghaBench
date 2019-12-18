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
struct tty_struct {int dummy; } ;
struct tty_ldisc {int dummy; } ;

/* Variables and functions */
 struct tty_ldisc* tty_ldisc_try (struct tty_struct*) ; 

struct tty_ldisc *tty_ldisc_ref(struct tty_struct *tty)
{
	return tty_ldisc_try(tty);
}