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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ipath_portdata {scalar_t__ port_hdrqfull; int port_head; int /*<<< orphan*/  port_port; } ;
struct ipath_devdata {scalar_t__ ipath_p0_hdrqfull; scalar_t__ ipath_last_tidfull; scalar_t__ ipath_lastport0rcv_cnt; int ipath_rhdrhead_intr_off; struct ipath_portdata** ipath_pd; } ;
struct TYPE_2__ {scalar_t__ sps_etidfull; scalar_t__ sps_hdrqfull; scalar_t__ sps_port0pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  PKT ; 
 int __IPATH_DBG ; 
 int __IPATH_PKTDBG ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,int,int,unsigned long long) ; 
 int /*<<< orphan*/  ipath_dbg (char*,char*) ; 
 int ipath_debug ; 
 int ipath_get_hdrqtail (struct ipath_portdata*) ; 
 TYPE_1__ ipath_stats ; 
 int /*<<< orphan*/  ipath_write_ureg (struct ipath_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  ur_rcvhdrhead ; 

__attribute__((used)) static void ipath_qcheck(struct ipath_devdata *dd)
{
	static u64 last_tot_hdrqfull;
	struct ipath_portdata *pd = dd->ipath_pd[0];
	size_t blen = 0;
	char buf[128];
	u32 hdrqtail;

	*buf = 0;
	if (pd->port_hdrqfull != dd->ipath_p0_hdrqfull) {
		blen = snprintf(buf, sizeof buf, "port 0 hdrqfull %u",
				pd->port_hdrqfull -
				dd->ipath_p0_hdrqfull);
		dd->ipath_p0_hdrqfull = pd->port_hdrqfull;
	}
	if (ipath_stats.sps_etidfull != dd->ipath_last_tidfull) {
		blen += snprintf(buf + blen, sizeof buf - blen,
				 "%srcvegrfull %llu",
				 blen ? ", " : "",
				 (unsigned long long)
				 (ipath_stats.sps_etidfull -
				  dd->ipath_last_tidfull));
		dd->ipath_last_tidfull = ipath_stats.sps_etidfull;
	}

	/*
	 * this is actually the number of hdrq full interrupts, not actual
	 * events, but at the moment that's mostly what I'm interested in.
	 * Actual count, etc. is in the counters, if needed.  For production
	 * users this won't ordinarily be printed.
	 */

	if ((ipath_debug & (__IPATH_PKTDBG | __IPATH_DBG)) &&
	    ipath_stats.sps_hdrqfull != last_tot_hdrqfull) {
		blen += snprintf(buf + blen, sizeof buf - blen,
				 "%shdrqfull %llu (all ports)",
				 blen ? ", " : "",
				 (unsigned long long)
				 (ipath_stats.sps_hdrqfull -
				  last_tot_hdrqfull));
		last_tot_hdrqfull = ipath_stats.sps_hdrqfull;
	}
	if (blen)
		ipath_dbg("%s\n", buf);

	hdrqtail = ipath_get_hdrqtail(pd);
	if (pd->port_head != hdrqtail) {
		if (dd->ipath_lastport0rcv_cnt ==
		    ipath_stats.sps_port0pkts) {
			ipath_cdbg(PKT, "missing rcv interrupts? "
				   "port0 hd=%x tl=%x; port0pkts %llx; write"
				   " hd (w/intr)\n",
				   pd->port_head, hdrqtail,
				   (unsigned long long)
				   ipath_stats.sps_port0pkts);
			ipath_write_ureg(dd, ur_rcvhdrhead, hdrqtail |
				dd->ipath_rhdrhead_intr_off, pd->port_port);
		}
		dd->ipath_lastport0rcv_cnt = ipath_stats.sps_port0pkts;
	}
}