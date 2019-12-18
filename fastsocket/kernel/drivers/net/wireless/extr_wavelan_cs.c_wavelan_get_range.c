#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {unsigned int base_addr; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_8__ {int level; int noise; void* qual; } ;
struct TYPE_7__ {int /*<<< orphan*/  noise; int /*<<< orphan*/  level; void* qual; } ;
struct iw_range {int we_version_source; double throughput; int min_nwid; int max_nwid; int sensitivity; int num_bitrates; int* bitrate; int* event_capa; int num_channels; int num_frequency; int* encoding_size; int num_encoding_sizes; int max_encoding_tokens; int /*<<< orphan*/  freq; TYPE_3__ avg_qual; TYPE_2__ max_qual; int /*<<< orphan*/  we_version_compiled; } ;
struct TYPE_9__ {int /*<<< orphan*/  spinlock; } ;
typedef  TYPE_4__ net_local ;

/* Variables and functions */
 int IW_EVENT_CAPA_K_1 ; 
 int IW_EVENT_CAPA_MASK (int) ; 
 int /*<<< orphan*/  IW_MAX_FREQUENCIES ; 
 int MMR_FEE_STATUS_BUSY ; 
 int MMR_FEE_STATUS_DWLD ; 
 void* MMR_SGNL_QUAL ; 
 int /*<<< orphan*/  MMR_SIGNAL_LVL ; 
 int /*<<< orphan*/  MMR_SILENCE_LVL ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmc_encr (unsigned int) ; 
 int mmc_in (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmr_fee_status ; 
 int /*<<< orphan*/  mmroff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wv_frequency_list (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wavelan_get_range(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu,
			     char *extra)
{
	unsigned int base = dev->base_addr;
	net_local *lp = netdev_priv(dev);
	struct iw_range *range = (struct iw_range *) extra;
	unsigned long flags;
	int ret = 0;

	/* Set the length (very important for backward compatibility) */
	wrqu->data.length = sizeof(struct iw_range);

	/* Set all the info we don't care or don't know about to zero */
	memset(range, 0, sizeof(struct iw_range));

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 9;

	/* Set information in the range struct.  */
	range->throughput = 1.4 * 1000 * 1000;	/* don't argue on this ! */
	range->min_nwid = 0x0000;
	range->max_nwid = 0xFFFF;

	range->sensitivity = 0x3F;
	range->max_qual.qual = MMR_SGNL_QUAL;
	range->max_qual.level = MMR_SIGNAL_LVL;
	range->max_qual.noise = MMR_SILENCE_LVL;
	range->avg_qual.qual = MMR_SGNL_QUAL; /* Always max */
	/* Need to get better values for those two */
	range->avg_qual.level = 30;
	range->avg_qual.noise = 8;

	range->num_bitrates = 1;
	range->bitrate[0] = 2000000;	/* 2 Mb/s */

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_MASK(0x8B02) |
				IW_EVENT_CAPA_MASK(0x8B04) |
				IW_EVENT_CAPA_MASK(0x8B06));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;

	/* Disable interrupts and save flags. */
	spin_lock_irqsave(&lp->spinlock, flags);
	
	/* Attempt to recognise 2.00 cards (2.4 GHz frequency selectable). */
	if (!(mmc_in(base, mmroff(0, mmr_fee_status)) &
	      (MMR_FEE_STATUS_DWLD | MMR_FEE_STATUS_BUSY))) {
		range->num_channels = 10;
		range->num_frequency = wv_frequency_list(base, range->freq,
							IW_MAX_FREQUENCIES);
	} else
		range->num_channels = range->num_frequency = 0;

	/* Encryption supported ? */
	if (mmc_encr(base)) {
		range->encoding_size[0] = 8;	/* DES = 64 bits key */
		range->num_encoding_sizes = 1;
		range->max_encoding_tokens = 1;	/* Only one key possible */
	} else {
		range->num_encoding_sizes = 0;
		range->max_encoding_tokens = 0;
	}

	/* Enable interrupts and restore flags. */
	spin_unlock_irqrestore(&lp->spinlock, flags);

	return ret;
}