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
struct r8192_priv {short crcmon; int /*<<< orphan*/  wx_sem; scalar_t__ up; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*,char*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r8192_wx_set_crcmon(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	int *parms = (int *)extra;
	int enable = (parms[0] > 0);
	short prev = priv->crcmon;

	down(&priv->wx_sem);

	if(enable)
		priv->crcmon=1;
	else
		priv->crcmon=0;

	DMESG("bad CRC in monitor mode are %s",
	      priv->crcmon ? "accepted" : "rejected");

	if(prev != priv->crcmon && priv->up){
		//rtl8180_down(dev);
		//rtl8180_up(dev);
	}

	up(&priv->wx_sem);

	return 0;
}