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
struct TYPE_2__ {int value; } ;
union iwreq_data {TYPE_1__ bitrate; } ;
typedef  int u32 ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {int mode; int rate; int /*<<< orphan*/  dev; scalar_t__ (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HTHalfMcsToDataRate (struct ieee80211_device*,int) ; 
 int HTMcsToDataRate (struct ieee80211_device*,int) ; 
 int IEEE_A ; 
 int IEEE_B ; 
 int IEEE_G ; 
 int IEEE_N_24G ; 
 int IEEE_N_5G ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

int ieee80211_wx_get_rate(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	u32 tmp_rate = 0;
	//printk("===>mode:%d, halfNmode:%d\n", ieee->mode, ieee->bHalfWirelessN24GMode);
	if (ieee->mode & (IEEE_A | IEEE_B | IEEE_G))
		tmp_rate = ieee->rate;
	else if (ieee->mode & IEEE_N_5G)
		tmp_rate = 580;
	else if (ieee->mode & IEEE_N_24G)
	{
		if (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
			tmp_rate = HTHalfMcsToDataRate(ieee, 15);
		else
			tmp_rate = HTMcsToDataRate(ieee, 15);
	}
	wrqu->bitrate.value = tmp_rate * 500000;

	return 0;
}