#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {scalar_t__ m; scalar_t__ e; } ;
struct TYPE_5__ {scalar_t__ a_hop_pattern; } ;
struct TYPE_6__ {TYPE_1__ b5; } ;
struct TYPE_7__ {scalar_t__ card_status; TYPE_2__ sparm; } ;
typedef  TYPE_3__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CARD_AWAITING_PARAM ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EOPNOTSUPP ; 
 scalar_t__ USA_HOP_MOD ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_set_freq(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_freq *fwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);
	int err = -EINPROGRESS;	/* Call commit handler */

	/* Reject if card is already initialised */
	if (local->card_status != CARD_AWAITING_PARAM)
		return -EBUSY;

	/* Setting by channel number */
	if ((fwrq->m > USA_HOP_MOD) || (fwrq->e > 0))
		err = -EOPNOTSUPP;
	else
		local->sparm.b5.a_hop_pattern = fwrq->m;

	return err;
}