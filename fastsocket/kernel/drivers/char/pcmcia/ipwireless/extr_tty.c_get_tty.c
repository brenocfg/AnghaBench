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
struct ipw_tty {int dummy; } ;
struct TYPE_2__ {int minor_start; } ;

/* Variables and functions */
 int IPWIRELESS_PCMCIA_MINORS ; 
 int IPWIRELESS_PCMCIA_MINOR_RANGE ; 
 int TTYTYPE_RAS_RAW ; 
 TYPE_1__* ipw_tty_driver ; 
 int /*<<< orphan*/  ipwireless_loopback ; 
 struct ipw_tty** ttys ; 

__attribute__((used)) static struct ipw_tty *get_tty(int minor)
{
	if (minor < ipw_tty_driver->minor_start
			|| minor >= ipw_tty_driver->minor_start +
			IPWIRELESS_PCMCIA_MINORS)
		return NULL;
	else {
		int minor_offset = minor - ipw_tty_driver->minor_start;

		/*
		 * The 'ras_raw' channel is only available when 'loopback' mode
		 * is enabled.
		 * Number of minor starts with 16 (_RANGE * _RAS_RAW).
		 */
		if (!ipwireless_loopback &&
				minor_offset >=
				 IPWIRELESS_PCMCIA_MINOR_RANGE * TTYTYPE_RAS_RAW)
			return NULL;

		return ttys[minor_offset];
	}
}