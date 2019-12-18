#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; scalar_t__ flags; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  updated; } ;
struct iw_statistics {TYPE_2__ qual; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IW_QUAL_ALL_UPDATED ; 
 struct iw_statistics* get_wireless_stats (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (char*,struct iw_statistics*,int) ; 

__attribute__((used)) static int iw_handler_get_iwstats(struct net_device *		dev,
				  struct iw_request_info *	info,
				  union iwreq_data *		wrqu,
				  char *			extra)
{
	/* Get stats from the driver */
	struct iw_statistics *stats;

	stats = get_wireless_stats(dev);
	if (stats) {
		/* Copy statistics to extra */
		memcpy(extra, stats, sizeof(struct iw_statistics));
		wrqu->data.length = sizeof(struct iw_statistics);

		/* Check if we need to clear the updated flag */
		if (wrqu->data.flags != 0)
			stats->qual.updated &= ~IW_QUAL_ALL_UPDATED;
		return 0;
	} else
		return -EOPNOTSUPP;
}