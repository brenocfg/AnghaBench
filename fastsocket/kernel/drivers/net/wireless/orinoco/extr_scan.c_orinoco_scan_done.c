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
struct orinoco_private {int /*<<< orphan*/ * scan_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,int) ; 

void orinoco_scan_done(struct orinoco_private *priv, bool abort)
{
	if (priv->scan_request) {
		cfg80211_scan_done(priv->scan_request, abort);
		priv->scan_request = NULL;
	}
}