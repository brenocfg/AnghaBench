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
typedef  int u32 ;
struct be_tx_stats {int tx_pkts; int /*<<< orphan*/  tx_stops; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_wrbs; int /*<<< orphan*/  tx_reqs; } ;
struct be_tx_obj {int dummy; } ;

/* Variables and functions */
 struct be_tx_stats* tx_stats (struct be_tx_obj*) ; 

__attribute__((used)) static void be_tx_stats_update(struct be_tx_obj *txo,
			u32 wrb_cnt, u32 copied, u32 gso_segs, bool stopped)
{
	struct be_tx_stats *stats = tx_stats(txo);

	stats->tx_reqs++;
	stats->tx_wrbs += wrb_cnt;
	stats->tx_bytes += copied;
	stats->tx_pkts += (gso_segs ? gso_segs : 1);
	if (stopped)
		stats->tx_stops++;
}