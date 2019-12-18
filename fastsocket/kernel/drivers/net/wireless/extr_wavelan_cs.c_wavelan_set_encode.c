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
struct TYPE_5__ {int length; int flags; } ;
union iwreq_data {TYPE_1__ encoding; } ;
struct net_device {unsigned int base_addr; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_6__ {int psa_encryption_select; int /*<<< orphan*/  psa_encryption_key; } ;
typedef  TYPE_2__ psa_t ;
struct TYPE_7__ {int /*<<< orphan*/  spinlock; } ;
typedef  TYPE_3__ net_local ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_ENCODE_DISABLED ; 
 int MMW_ENCR_ENABLE_EN ; 
 int MMW_ENCR_ENABLE_MODE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmc_encr (unsigned int) ; 
 int /*<<< orphan*/  mmc_out (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_write (unsigned int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  mmw_encr_enable ; 
 int /*<<< orphan*/  mmw_encr_key ; 
 int /*<<< orphan*/  mmwoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  psa_write (struct net_device*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_psa_checksum (struct net_device*) ; 

__attribute__((used)) static int wavelan_set_encode(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *wrqu,
			      char *extra)
{
	unsigned int base = dev->base_addr;
	net_local *lp = netdev_priv(dev);
	unsigned long flags;
	psa_t psa;
	int ret = 0;

	/* Disable interrupts and save flags. */
	spin_lock_irqsave(&lp->spinlock, flags);

	/* Check if capable of encryption */
	if (!mmc_encr(base)) {
		ret = -EOPNOTSUPP;
	}

	/* Check the size of the key */
	if((wrqu->encoding.length != 8) && (wrqu->encoding.length != 0)) {
		ret = -EINVAL;
	}

	if(!ret) {
		/* Basic checking... */
		if (wrqu->encoding.length == 8) {
			/* Copy the key in the driver */
			memcpy(psa.psa_encryption_key, extra,
			       wrqu->encoding.length);
			psa.psa_encryption_select = 1;

			psa_write(dev,
				  (char *) &psa.psa_encryption_select -
				  (char *) &psa,
				  (unsigned char *) &psa.
				  psa_encryption_select, 8 + 1);

			mmc_out(base, mmwoff(0, mmw_encr_enable),
				MMW_ENCR_ENABLE_EN | MMW_ENCR_ENABLE_MODE);
			mmc_write(base, mmwoff(0, mmw_encr_key),
				  (unsigned char *) &psa.
				  psa_encryption_key, 8);
		}

		/* disable encryption */
		if (wrqu->encoding.flags & IW_ENCODE_DISABLED) {
			psa.psa_encryption_select = 0;
			psa_write(dev,
				  (char *) &psa.psa_encryption_select -
				  (char *) &psa,
				  (unsigned char *) &psa.
				  psa_encryption_select, 1);

			mmc_out(base, mmwoff(0, mmw_encr_enable), 0);
		}
		/* update the Wavelan checksum */
		update_psa_checksum(dev);
	}

	/* Enable interrupts and restore flags. */
	spin_unlock_irqrestore(&lp->spinlock, flags);

	return ret;
}