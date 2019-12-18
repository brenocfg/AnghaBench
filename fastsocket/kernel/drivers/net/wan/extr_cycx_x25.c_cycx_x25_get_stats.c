#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tx_errors; scalar_t__ collisions; scalar_t__ tx_dropped; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_packets; scalar_t__ rx_errors; scalar_t__ rx_dropped; int /*<<< orphan*/  rx_missed_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_10__ {TYPE_4__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_aborts; int /*<<< orphan*/  n2_tx_frames; int /*<<< orphan*/  rx_aborts; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  n2_rx_frames; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;
struct TYPE_8__ {TYPE_2__ x; } ;
struct cycx_device {TYPE_5__ wandev; TYPE_3__ u; int /*<<< orphan*/  wait_stats; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  X25_STATISTIC ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  cycx_x25_dump_devs (TYPE_5__*) ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int x25_exec (struct cycx_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cycx_x25_get_stats(struct cycx_device *card)
{
	/* the firmware expects 20 in the size field!!!
	   thanks to Daniela */
	int err = x25_exec(card, X25_STATISTIC, 0, NULL, 20, NULL, 0);

	if (err)
		return err;

	interruptible_sleep_on(&card->wait_stats);

	if (signal_pending(current))
		return -EINTR;

	card->wandev.stats.rx_packets = card->u.x.stats.n2_rx_frames;
	card->wandev.stats.rx_over_errors = card->u.x.stats.rx_over_errors;
	card->wandev.stats.rx_crc_errors = card->u.x.stats.rx_crc_errors;
	card->wandev.stats.rx_length_errors = 0; /* not available from fw */
	card->wandev.stats.rx_frame_errors = 0; /* not available from fw */
	card->wandev.stats.rx_missed_errors = card->u.x.stats.rx_aborts;
	card->wandev.stats.rx_dropped = 0; /* not available from fw */
	card->wandev.stats.rx_errors = 0; /* not available from fw */
	card->wandev.stats.tx_packets = card->u.x.stats.n2_tx_frames;
	card->wandev.stats.tx_aborted_errors = card->u.x.stats.tx_aborts;
	card->wandev.stats.tx_dropped = 0; /* not available from fw */
	card->wandev.stats.collisions = 0; /* not available from fw */
	card->wandev.stats.tx_errors = 0; /* not available from fw */

	cycx_x25_dump_devs(&card->wandev);

	return 0;
}