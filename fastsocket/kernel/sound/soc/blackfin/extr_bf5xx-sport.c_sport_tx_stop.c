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
struct sport_device {scalar_t__ tx_run; int /*<<< orphan*/ * curr_tx_desc; int /*<<< orphan*/ * curr_rx_desc; scalar_t__ rx_run; } ;

/* Variables and functions */
 int /*<<< orphan*/  sport_hook_tx_dummy (struct sport_device*) ; 
 int /*<<< orphan*/  sport_stop (struct sport_device*) ; 

int sport_tx_stop(struct sport_device *sport)
{
	if (!sport->tx_run)
		return 0;
	if (sport->rx_run) {
		/* RX is still running, hook the dummy buffer */
		sport_hook_tx_dummy(sport);
	} else {
		/* Both rx and tx dma stopped */
		sport_stop(sport);
		sport->curr_rx_desc = NULL;
		sport->curr_tx_desc = NULL;
	}

	sport->tx_run = 0;

	return 0;
}