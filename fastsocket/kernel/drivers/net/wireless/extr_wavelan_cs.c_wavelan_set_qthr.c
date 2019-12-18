#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {unsigned int base_addr; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  psa_quality_thr; } ;
typedef  TYPE_1__ psa_t ;
struct TYPE_5__ {int /*<<< orphan*/  spinlock; } ;
typedef  TYPE_2__ net_local ;
typedef  int /*<<< orphan*/ * extra ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_out (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmw_quality_thr ; 
 int /*<<< orphan*/  mmwoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  psa_write (struct net_device*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_psa_checksum (struct net_device*) ; 

__attribute__((used)) static int wavelan_set_qthr(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu,
			    char *extra)
{
	unsigned int base = dev->base_addr;
	net_local *lp = netdev_priv(dev);
	psa_t psa;
	unsigned long flags;

	/* Disable interrupts and save flags. */
	spin_lock_irqsave(&lp->spinlock, flags);
	
	psa.psa_quality_thr = *(extra) & 0x0F;
	psa_write(dev,
		  (char *) &psa.psa_quality_thr - (char *) &psa,
		  (unsigned char *) &psa.psa_quality_thr, 1);
	/* update the Wavelan checksum */
	update_psa_checksum(dev);
	mmc_out(base, mmwoff(0, mmw_quality_thr),
		psa.psa_quality_thr);

	/* Enable interrupts and restore flags. */
	spin_unlock_irqrestore(&lp->spinlock, flags);

	return 0;
}