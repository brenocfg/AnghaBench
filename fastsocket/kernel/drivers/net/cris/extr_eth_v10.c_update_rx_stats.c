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
struct net_device_stats {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;

/* Variables and functions */
 scalar_t__ IO_EXTRACT (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long* R_REC_COUNTERS ; 
 int /*<<< orphan*/  alignment_error ; 
 int /*<<< orphan*/  congestion ; 
 int /*<<< orphan*/  crc_error ; 
 int /*<<< orphan*/  oversize ; 

__attribute__((used)) static void
update_rx_stats(struct net_device_stats *es)
{
	unsigned long r = *R_REC_COUNTERS;
	/* update stats relevant to reception errors */
	es->rx_fifo_errors += IO_EXTRACT(R_REC_COUNTERS, congestion, r);
	es->rx_crc_errors += IO_EXTRACT(R_REC_COUNTERS, crc_error, r);
	es->rx_frame_errors += IO_EXTRACT(R_REC_COUNTERS, alignment_error, r);
	es->rx_length_errors += IO_EXTRACT(R_REC_COUNTERS, oversize, r);
}