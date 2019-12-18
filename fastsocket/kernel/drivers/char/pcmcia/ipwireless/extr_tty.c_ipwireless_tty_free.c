#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipw_tty {size_t index; int closing; int /*<<< orphan*/  ipw_tty_mutex; int /*<<< orphan*/  channel_idx; scalar_t__ open_count; int /*<<< orphan*/ * linux_tty; struct ipw_network* network; } ;
struct ipw_network {int dummy; } ;
struct TYPE_3__ {scalar_t__ minor_start; } ;

/* Variables and functions */
 int IPWIRELESS_PCMCIA_MINORS ; 
 scalar_t__ IPWIRELESS_PCMCIA_MINOR_RANGE ; 
 int /*<<< orphan*/  do_ipw_close (struct ipw_tty*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 struct ipw_tty* get_tty (scalar_t__) ; 
 TYPE_1__* ipw_tty_driver ; 
 int /*<<< orphan*/  ipwireless_disassociate_network_ttys (struct ipw_network*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipw_tty*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_deregistering (struct ipw_tty*) ; 
 int /*<<< orphan*/  tty_hangup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (TYPE_1__*,int) ; 
 struct ipw_tty** ttys ; 

void ipwireless_tty_free(struct ipw_tty *tty)
{
	int j;
	struct ipw_network *network = ttys[tty->index]->network;

	for (j = tty->index; j < IPWIRELESS_PCMCIA_MINORS;
			j += IPWIRELESS_PCMCIA_MINOR_RANGE) {
		struct ipw_tty *ttyj = ttys[j];

		if (ttyj) {
			mutex_lock(&ttyj->ipw_tty_mutex);
			if (get_tty(j + ipw_tty_driver->minor_start) == ttyj)
				report_deregistering(ttyj);
			ttyj->closing = 1;
			if (ttyj->linux_tty != NULL) {
				mutex_unlock(&ttyj->ipw_tty_mutex);
				tty_hangup(ttyj->linux_tty);
				/* Wait till the tty_hangup has completed */
				flush_scheduled_work();
				/* FIXME: Exactly how is the tty object locked here
				   against a parallel ioctl etc */
				mutex_lock(&ttyj->ipw_tty_mutex);
			}
			while (ttyj->open_count)
				do_ipw_close(ttyj);
			ipwireless_disassociate_network_ttys(network,
							     ttyj->channel_idx);
			tty_unregister_device(ipw_tty_driver, j);
			ttys[j] = NULL;
			mutex_unlock(&ttyj->ipw_tty_mutex);
			kfree(ttyj);
		}
	}
}