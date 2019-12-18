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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {int /*<<< orphan*/  ieee; } ;

/* Variables and functions */
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int libipw_wx_get_encode (int /*<<< orphan*/ ,struct iw_request_info*,union iwreq_data*,char*) ; 

__attribute__((used)) static int ipw_wx_get_encode(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *key)
{
	struct ipw_priv *priv = libipw_priv(dev);
	return libipw_wx_get_encode(priv->ieee, info, wrqu, key);
}