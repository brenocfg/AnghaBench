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
struct TYPE_2__ {scalar_t__ value; int disabled; scalar_t__ fixed; } ;
union iwreq_data {TYPE_1__ rts; } ;
struct iw_request_info {int dummy; } ;
struct ieee80211_device {scalar_t__ rts; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RTS_THRESHOLD ; 

int ieee80211_wx_get_rts(struct ieee80211_device *ieee,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	wrqu->rts.value = ieee->rts;
	wrqu->rts.fixed = 0;	/* no auto select */
	wrqu->rts.disabled = (wrqu->rts.value == DEFAULT_RTS_THRESHOLD);
	return 0;
}