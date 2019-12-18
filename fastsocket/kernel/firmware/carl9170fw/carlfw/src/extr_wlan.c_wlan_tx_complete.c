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
struct TYPE_2__ {int /*<<< orphan*/  cnt; int /*<<< orphan*/  rix; scalar_t__ cookie; int /*<<< orphan*/  queue; } ;
struct carl9170_tx_superframe {TYPE_1__ s; } ;
struct carl9170_tx_status {int success; int /*<<< orphan*/  tries; int /*<<< orphan*/  rix; int /*<<< orphan*/  queue; scalar_t__ cookie; } ;

/* Variables and functions */
 struct carl9170_tx_status* wlan_get_tx_status_buffer () ; 

void wlan_tx_complete(struct carl9170_tx_superframe *super,
		      bool txs)
{
	struct carl9170_tx_status *status;

	status = wlan_get_tx_status_buffer();

	/*
	 * The *unique* cookie and AC_ID is used by the driver for
	 * frame lookup.
	 */
	status->cookie = super->s.cookie;
	status->queue = super->s.queue;
	super->s.cookie = 0;

	/*
	 * This field holds the number of tries of the rate in
	 * the rate index field (rix).
	 */
	status->rix = super->s.rix;
	status->tries = super->s.cnt;
	status->success = (txs) ? 1 : 0;
}