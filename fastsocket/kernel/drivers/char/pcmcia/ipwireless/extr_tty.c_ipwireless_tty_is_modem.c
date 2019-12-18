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
struct ipw_tty {scalar_t__ tty_type; } ;

/* Variables and functions */
 scalar_t__ TTYTYPE_MODEM ; 

int ipwireless_tty_is_modem(struct ipw_tty *tty)
{
	return tty->tty_type == TTYTYPE_MODEM;
}