#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct region_channel {scalar_t__ band; int nrcfp; struct chan_freq_power* CFP; int /*<<< orphan*/  valid; } ;
struct lbs_private {struct region_channel* universal_channel; scalar_t__ enable11d; struct region_channel* region_channel; } ;
struct chan_freq_power {scalar_t__ channel; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct region_channel*) ; 
 int /*<<< orphan*/  lbs_deb_wext (char*,scalar_t__,scalar_t__) ; 

struct chan_freq_power *lbs_find_cfp_by_band_and_channel(
	struct lbs_private *priv,
	u8 band,
	u16 channel)
{
	struct chan_freq_power *cfp = NULL;
	struct region_channel *rc;
	int i, j;

	for (j = 0; !cfp && (j < ARRAY_SIZE(priv->region_channel)); j++) {
		rc = &priv->region_channel[j];

		if (priv->enable11d)
			rc = &priv->universal_channel[j];
		if (!rc->valid || !rc->CFP)
			continue;
		if (rc->band != band)
			continue;
		for (i = 0; i < rc->nrcfp; i++) {
			if (rc->CFP[i].channel == channel) {
				cfp = &rc->CFP[i];
				break;
			}
		}
	}

	if (!cfp && channel)
		lbs_deb_wext("lbs_find_cfp_by_band_and_channel: can't find "
		       "cfp by band %d / channel %d\n", band, channel);

	return cfp;
}