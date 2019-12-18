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
struct TYPE_5__ {char a_network_type; } ;
struct TYPE_6__ {TYPE_1__ b5; } ;
struct TYPE_7__ {scalar_t__ card_status; TYPE_2__ sparm; } ;
typedef  TYPE_3__ ray_dev_t ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ CARD_AWAITING_PARAM ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
#define  IW_MODE_ADHOC 129 
#define  IW_MODE_INFRA 128 
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_set_mode(struct net_device *dev,
			struct iw_request_info *info, __u32 *uwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);
	int err = -EINPROGRESS;	/* Call commit handler */
	char card_mode = 1;

	/* Reject if card is already initialised */
	if (local->card_status != CARD_AWAITING_PARAM)
		return -EBUSY;

	switch (*uwrq) {
	case IW_MODE_ADHOC:
		card_mode = 0;
		/* Fall through */
	case IW_MODE_INFRA:
		local->sparm.b5.a_network_type = card_mode;
		break;
	default:
		err = -EINVAL;
	}

	return err;
}