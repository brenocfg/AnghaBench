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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__* np_hist_bars; int /*<<< orphan*/  np_hist5; int /*<<< orphan*/  np_hist4; int /*<<< orphan*/  np_hist3; int /*<<< orphan*/  np_hist2; int /*<<< orphan*/  np_hist1; } ;
typedef  TYPE_1__ net_perf_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic64 (scalar_t__,int /*<<< orphan*/ *) ; 

void
net_perf_histogram(net_perf_t *npp, uint64_t num_pkts)
{
	if (num_pkts <= npp->np_hist_bars[0]) {
		OSAddAtomic64(num_pkts, &npp->np_hist1);
	} else if (npp->np_hist_bars[0] < num_pkts && num_pkts <= npp->np_hist_bars[1]) {
		OSAddAtomic64(num_pkts, &npp->np_hist2);
	} else if (npp->np_hist_bars[1] < num_pkts && num_pkts <= npp->np_hist_bars[2]) {
		OSAddAtomic64(num_pkts, &npp->np_hist3);
	} else if (npp->np_hist_bars[2] < num_pkts && num_pkts <= npp->np_hist_bars[3]) {
		OSAddAtomic64(num_pkts, &npp->np_hist4);
	} else if (npp->np_hist_bars[3] < num_pkts) {
		OSAddAtomic64(num_pkts, &npp->np_hist5);
	}
}