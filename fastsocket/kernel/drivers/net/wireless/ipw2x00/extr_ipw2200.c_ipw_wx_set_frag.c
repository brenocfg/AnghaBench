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
struct TYPE_4__ {int value; int /*<<< orphan*/  fixed; scalar_t__ disabled; } ;
union iwreq_data {TYPE_2__ frag; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int /*<<< orphan*/  mutex; TYPE_1__* ieee; } ;
struct TYPE_3__ {int fts; } ;

/* Variables and functions */
 int DEFAULT_FTS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*,int) ; 
 int MAX_FRAG_THRESHOLD ; 
 int MIN_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  ipw_send_frag_threshold (struct ipw_priv*,int) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_frag(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	mutex_lock(&priv->mutex);
	if (wrqu->frag.disabled || !wrqu->frag.fixed)
		priv->ieee->fts = DEFAULT_FTS;
	else {
		if (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD) {
			mutex_unlock(&priv->mutex);
			return -EINVAL;
		}

		priv->ieee->fts = wrqu->frag.value & ~0x1;
	}

	ipw_send_frag_threshold(priv, wrqu->frag.value);
	mutex_unlock(&priv->mutex);
	IPW_DEBUG_WX("SET Frag Threshold -> %d\n", wrqu->frag.value);
	return 0;
}