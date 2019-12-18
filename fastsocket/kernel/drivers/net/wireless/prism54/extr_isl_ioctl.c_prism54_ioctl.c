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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct iwreq {TYPE_1__ u; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  PRISM54_HOSTAPD 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int prism54_hostapd (struct net_device*,int /*<<< orphan*/ *) ; 

int
prism54_ioctl(struct net_device *ndev, struct ifreq *rq, int cmd)
{
	struct iwreq *wrq = (struct iwreq *) rq;
	int ret = -1;
	switch (cmd) {
		case PRISM54_HOSTAPD:
		if (!capable(CAP_NET_ADMIN))
		return -EPERM;
		ret = prism54_hostapd(ndev, &wrq->u.data);
		return ret;
	}
	return -EOPNOTSUPP;
}