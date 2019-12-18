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
struct at91mci_host {int flags; TYPE_1__* request; int /*<<< orphan*/  mmc; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {scalar_t__ stop; scalar_t__ cmd; } ;

/* Variables and functions */
 int FL_SENT_COMMAND ; 
 int FL_SENT_STOP ; 
 int /*<<< orphan*/  at91_mci_send_command (struct at91mci_host*,scalar_t__) ; 
 int /*<<< orphan*/  at91_reset_host (struct at91mci_host*) ; 
 scalar_t__ cpu_is_at91rm9200 () ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void at91_mci_process_next(struct at91mci_host *host)
{
	if (!(host->flags & FL_SENT_COMMAND)) {
		host->flags |= FL_SENT_COMMAND;
		at91_mci_send_command(host, host->request->cmd);
	}
	else if ((!(host->flags & FL_SENT_STOP)) && host->request->stop) {
		host->flags |= FL_SENT_STOP;
		at91_mci_send_command(host, host->request->stop);
	} else {
		del_timer(&host->timer);
		/* the at91rm9200 mci controller hangs after some transfers,
		 * and the workaround is to reset it after each transfer.
		 */
		if (cpu_is_at91rm9200())
			at91_reset_host(host);
		mmc_request_done(host->mmc, host->request);
	}
}