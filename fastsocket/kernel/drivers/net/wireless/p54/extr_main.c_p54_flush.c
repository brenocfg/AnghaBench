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
typedef  int /*<<< orphan*/  u32 ;
struct p54_common {int dummy; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int P54_STATISTICS_UPDATE ; 
 int /*<<< orphan*/  WARN (unsigned int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ p54_flush_count (struct p54_common*) ; 

__attribute__((used)) static void p54_flush(struct ieee80211_hw *dev, u32 queues, bool drop)
{
	struct p54_common *priv = dev->priv;
	unsigned int total, i;

	/*
	 * Currently, it wouldn't really matter if we wait for one second
	 * or 15 minutes. But once someone gets around and completes the
	 * TODOs [ancel stuck frames / reset device] in p54_work, it will
	 * suddenly make sense to wait that long.
	 */
	i = P54_STATISTICS_UPDATE * 2 / 20;

	/*
	 * In this case no locking is required because as we speak the
	 * queues have already been stopped and no new frames can sneak
	 * up from behind.
	 */
	while ((total = p54_flush_count(priv) && i--)) {
		/* waste time */
		msleep(20);
	}

	WARN(total, "tx flush timeout, unresponsive firmware");
}