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
struct TYPE_2__ {int value; int fixed; } ;
union iwreq_data {TYPE_1__ bitrate; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int wl3501_get_rate(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	/*
	 * FIXME: have to see from where to get this info, perhaps this card
	 * works at 1 Mbit/s too... for now leave at 2 Mbit/s that is the most
	 * common with the Planet Access Points. -acme
	 */
	wrqu->bitrate.value = 2000000;
	wrqu->bitrate.fixed = 1;
	return 0;
}