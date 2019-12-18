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
struct iw_param {int value; int disabled; int fixed; } ;
struct TYPE_5__ {int* a_rts_threshold; } ;
struct TYPE_6__ {TYPE_1__ b5; } ;
struct TYPE_7__ {TYPE_2__ sparm; } ;
typedef  TYPE_3__ ray_dev_t ;

/* Variables and functions */
 TYPE_3__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ray_get_rts(struct net_device *dev,
		       struct iw_request_info *info,
		       struct iw_param *vwrq, char *extra)
{
	ray_dev_t *local = netdev_priv(dev);

	vwrq->value = (local->sparm.b5.a_rts_threshold[0] << 8)
	    + local->sparm.b5.a_rts_threshold[1];
	vwrq->disabled = (vwrq->value == 32767);
	vwrq->fixed = 1;

	return 0;
}