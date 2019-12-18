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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct libipw_device {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; int /*<<< orphan*/  wpa_enabled; } ;
struct iw_request_info {int dummy; } ;
struct ipw2100_priv {struct libipw_device* ieee; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_WPA_IE_LEN ; 
 int /*<<< orphan*/  ipw2100_wpa_assoc_frame (struct ipw2100_priv*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static int ipw2100_wx_set_genie(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{

	struct ipw2100_priv *priv = libipw_priv(dev);
	struct libipw_device *ieee = priv->ieee;
	u8 *buf;

	if (!ieee->wpa_enabled)
		return -EOPNOTSUPP;

	if (wrqu->data.length > MAX_WPA_IE_LEN ||
	    (wrqu->data.length && extra == NULL))
		return -EINVAL;

	if (wrqu->data.length) {
		buf = kmemdup(extra, wrqu->data.length, GFP_KERNEL);
		if (buf == NULL)
			return -ENOMEM;

		kfree(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_len = wrqu->data.length;
	} else {
		kfree(ieee->wpa_ie);
		ieee->wpa_ie = NULL;
		ieee->wpa_ie_len = 0;
	}

	ipw2100_wpa_assoc_frame(priv, ieee->wpa_ie, ieee->wpa_ie_len);

	return 0;
}