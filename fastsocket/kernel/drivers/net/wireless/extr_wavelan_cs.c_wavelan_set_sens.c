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
struct TYPE_5__ {int value; } ;
union iwreq_data {TYPE_1__ sens; } ;
struct net_device {unsigned int base_addr; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_6__ {int psa_thr_pre_set; } ;
typedef  TYPE_2__ psa_t ;
struct TYPE_7__ {int /*<<< orphan*/  spinlock; } ;
typedef  TYPE_3__ net_local ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_out (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmw_thr_pre_set ; 
 int /*<<< orphan*/  mmwoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  psa_write (struct net_device*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_psa_checksum (struct net_device*) ; 

__attribute__((used)) static int wavelan_set_sens(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu,
			    char *extra)
{
	unsigned int base = dev->base_addr;
	net_local *lp = netdev_priv(dev);
	psa_t psa;
	unsigned long flags;
	int ret = 0;

	/* Disable interrupts and save flags. */
	spin_lock_irqsave(&lp->spinlock, flags);
	
	/* Set the level threshold. */
	/* We should complain loudly if wrqu->sens.fixed = 0, because we
	 * can't set auto mode... */
	psa.psa_thr_pre_set = wrqu->sens.value & 0x3F;
	psa_write(dev,
		  (char *) &psa.psa_thr_pre_set - (char *) &psa,
		  (unsigned char *) &psa.psa_thr_pre_set, 1);
	/* update the Wavelan checksum */
	update_psa_checksum(dev);
	mmc_out(base, mmwoff(0, mmw_thr_pre_set),
		psa.psa_thr_pre_set);

	/* Enable interrupts and restore flags. */
	spin_unlock_irqrestore(&lp->spinlock, flags);

	return ret;
}