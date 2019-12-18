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
typedef  size_t u32 ;
struct ipath_portdata {scalar_t__ port_head; size_t port_lastrcvhdrqtail; int /*<<< orphan*/  port_wait; int /*<<< orphan*/  port_hdrqfull; int /*<<< orphan*/  port_cnt; } ;
struct ipath_devdata {size_t ipath_cfgports; int ipath_flags; size_t ipath_hdrqlast; struct ipath_portdata** ipath_pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  sps_hdrqfull; } ;

/* Variables and functions */
 int IPATH_NODMA_RTAIL ; 
 scalar_t__ ipath_get_hdrqtail (struct ipath_portdata*) ; 
 size_t ipath_get_rcvhdrtail (struct ipath_portdata*) ; 
 size_t ipath_read_ureg32 (struct ipath_devdata*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ ipath_stats ; 
 int /*<<< orphan*/  ur_rcvhdrhead ; 
 int /*<<< orphan*/  ur_rcvhdrtail ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int handle_hdrq_full(struct ipath_devdata *dd)
{
	int chkerrpkts = 0;
	u32 hd, tl;
	u32 i;

	ipath_stats.sps_hdrqfull++;
	for (i = 0; i < dd->ipath_cfgports; i++) {
		struct ipath_portdata *pd = dd->ipath_pd[i];

		if (i == 0) {
			/*
			 * For kernel receive queues, we just want to know
			 * if there are packets in the queue that we can
			 * process.
			 */
			if (pd->port_head != ipath_get_hdrqtail(pd))
				chkerrpkts |= 1 << i;
			continue;
		}

		/* Skip if user context is not open */
		if (!pd || !pd->port_cnt)
			continue;

		/* Don't report the same point multiple times. */
		if (dd->ipath_flags & IPATH_NODMA_RTAIL)
			tl = ipath_read_ureg32(dd, ur_rcvhdrtail, i);
		else
			tl = ipath_get_rcvhdrtail(pd);
		if (tl == pd->port_lastrcvhdrqtail)
			continue;

		hd = ipath_read_ureg32(dd, ur_rcvhdrhead, i);
		if (hd == (tl + 1) || (!hd && tl == dd->ipath_hdrqlast)) {
			pd->port_lastrcvhdrqtail = tl;
			pd->port_hdrqfull++;
			/* flush hdrqfull so that poll() sees it */
			wmb();
			wake_up_interruptible(&pd->port_wait);
		}
	}

	return chkerrpkts;
}