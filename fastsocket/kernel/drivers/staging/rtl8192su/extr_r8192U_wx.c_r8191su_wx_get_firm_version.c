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
typedef  int /*<<< orphan*/  u16 ;
struct r8192_priv {int /*<<< orphan*/  wx_sem; TYPE_1__* pFirmware; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int fixed; int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  FirmwareVersion; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8191su_wx_get_firm_version(struct net_device *dev,
		struct iw_request_info *info,
		struct iw_param *wrqu, char *extra)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u16 firmware_version;

	down(&priv->wx_sem);
	firmware_version = priv->pFirmware->FirmwareVersion;
	wrqu->value = firmware_version;
	wrqu->fixed = 1;

	up(&priv->wx_sem);
	return 0;
}