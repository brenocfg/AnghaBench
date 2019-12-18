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
union iwreq_data {int mode; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  spinlock; } ;
typedef  TYPE_1__ net_local ;

/* Variables and functions */
 int EINVAL ; 
#define  IW_MODE_ADHOC 129 
#define  IW_MODE_INFRA 128 
 int do_roaming ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wv_roam_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  wv_roam_init (struct net_device*) ; 

__attribute__((used)) static int wavelan_set_mode(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu,
			    char *extra)
{
	net_local *lp = netdev_priv(dev);
	unsigned long flags;
	int ret = 0;

	/* Disable interrupts and save flags. */
	spin_lock_irqsave(&lp->spinlock, flags);

	/* Check mode */
	switch(wrqu->mode) {
	case IW_MODE_ADHOC:
		if(do_roaming) {
			wv_roam_cleanup(dev);
			do_roaming = 0;
		}
		break;
	case IW_MODE_INFRA:
		if(!do_roaming) {
			wv_roam_init(dev);
			do_roaming = 1;
		}
		break;
	default:
		ret = -EINVAL;
	}

	/* Enable interrupts and restore flags. */
	spin_unlock_irqrestore(&lp->spinlock, flags);

	return ret;
}