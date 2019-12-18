#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {scalar_t__ length; } ;
struct TYPE_3__ {scalar_t__ nickname; } ;
typedef  int /*<<< orphan*/  PSTRING ;
typedef  TYPE_1__* PRTMP_ADAPTER ;

/* Variables and functions */
 int ENETDOWN ; 
 TYPE_1__* RTMP_OS_NETDEV_GET_PRIV (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int rt_ioctl_giwnickn(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *nickname)
{
	PRTMP_ADAPTER pAdapter = RTMP_OS_NETDEV_GET_PRIV(dev);

	if (pAdapter == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	if (data->length > strlen((PSTRING) pAdapter->nickname) + 1)
		data->length = strlen((PSTRING) pAdapter->nickname) + 1;
	if (data->length > 0) {
		memcpy(nickname, pAdapter->nickname, data->length-1);
		nickname[data->length-1] = '\0';
	}
	return 0;
}