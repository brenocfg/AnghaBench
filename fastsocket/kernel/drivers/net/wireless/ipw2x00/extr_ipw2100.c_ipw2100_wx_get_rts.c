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
struct TYPE_2__ {int value; int fixed; int disabled; } ;
union iwreq_data {TYPE_1__ rts; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {int rts_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
 int RTS_DISABLED ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw2100_wx_get_rts(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *wrqu, char *extra)
{
	/*
	 * This can be called at any time.  No action lock required
	 */

	struct ipw2100_priv *priv = libipw_priv(dev);

	wrqu->rts.value = priv->rts_threshold & ~RTS_DISABLED;
	wrqu->rts.fixed = 1;	/* no auto select */

	/* If RTS is set to the default value, then it is disabled */
	wrqu->rts.disabled = (priv->rts_threshold & RTS_DISABLED) ? 1 : 0;

	IPW_DEBUG_WX("GET RTS Threshold -> 0x%08X\n", wrqu->rts.value);

	return 0;
}