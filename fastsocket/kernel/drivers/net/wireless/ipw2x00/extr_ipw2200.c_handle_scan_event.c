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
struct TYPE_2__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct ipw_priv {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  scan_event; scalar_t__ user_requested_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_scan_event(struct ipw_priv *priv)
{
	/* Only userspace-requested scan completion events go out immediately */
	if (!priv->user_requested_scan) {
		if (!delayed_work_pending(&priv->scan_event))
			schedule_delayed_work(&priv->scan_event,
					      round_jiffies_relative(msecs_to_jiffies(4000)));
	} else {
		union iwreq_data wrqu;

		priv->user_requested_scan = 0;
		cancel_delayed_work(&priv->scan_event);

		wrqu.data.length = 0;
		wrqu.data.flags = 0;
		wireless_send_event(priv->net_dev, SIOCGIWSCAN, &wrqu, NULL);
	}
}