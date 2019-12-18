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
struct iw_param {int value; scalar_t__ disabled; } ;
struct TYPE_5__ {int* a_rts_threshold; } ;
struct TYPE_6__ {TYPE_1__ b5; } ;
struct TYPE_7__ {scalar_t__ card_status; TYPE_2__ sparm; } ;
typedef  TYPE_3__ ray_dev_t ;

/* Variables and functions */
 scalar_t__ CARD_AWAITING_PARAM ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_set_rts(struct net_device *dev,
		       struct iw_request_info *info,
		       struct iw_param *vwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);
	int rthr = vwrq->value;

	/* Reject if card is already initialised */
	if (local->card_status != CARD_AWAITING_PARAM)
		return -EBUSY;

	/* if(wrq->u.rts.fixed == 0) we should complain */
	if (vwrq->disabled)
		rthr = 32767;
	else {
		if ((rthr < 0) || (rthr > 2347))   /* What's the max packet size ??? */
			return -EINVAL;
	}
	local->sparm.b5.a_rts_threshold[0] = (rthr >> 8) & 0xFF;
	local->sparm.b5.a_rts_threshold[1] = rthr & 0xFF;

	return -EINPROGRESS;	/* Call commit handler */
}