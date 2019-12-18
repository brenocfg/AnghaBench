#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct region_channel {int /*<<< orphan*/  band; int /*<<< orphan*/  CFP; int /*<<< orphan*/  valid; } ;
struct parsed_region_chan_11d {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;
struct lbs_private {int /*<<< orphan*/  domainreg; int /*<<< orphan*/  parsed_region_chan; TYPE_1__ curbssparams; struct region_channel* region_channel; scalar_t__ enable11d; } ;
struct lbs_802_11d_domain_reg {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct region_channel*) ; 
 int /*<<< orphan*/  LBS_DEB_11D ; 
 int /*<<< orphan*/  generate_domain_info_11d (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_11d (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_generate_parsed_region_chan_11d (struct region_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int set_domain_info_11d (struct lbs_private*) ; 

int lbs_create_dnld_countryinfo_11d(struct lbs_private *priv)
{
	int ret;
	struct region_channel *region_chan;
	u8 j;

	lbs_deb_enter(LBS_DEB_11D);
	lbs_deb_11d("curbssparams.band %d\n", priv->curbssparams.band);

	if (priv->enable11d) {
		/* update parsed_region_chan_11; dnld domaininf to FW */

		for (j = 0; j < ARRAY_SIZE(priv->region_channel); j++) {
			region_chan = &priv->region_channel[j];

			lbs_deb_11d("%d region_chan->band %d\n", j,
			       region_chan->band);

			if (!region_chan || !region_chan->valid
			    || !region_chan->CFP)
				continue;
			if (region_chan->band != priv->curbssparams.band)
				continue;
			break;
		}

		if (j >= ARRAY_SIZE(priv->region_channel)) {
			lbs_deb_11d("region_chan not found, band %d\n",
			       priv->curbssparams.band);
			ret = -1;
			goto done;
		}

		memset(&priv->parsed_region_chan, 0,
		       sizeof(struct parsed_region_chan_11d));
		lbs_generate_parsed_region_chan_11d(region_chan,
						     &priv->
						     parsed_region_chan);

		memset(&priv->domainreg, 0,
		       sizeof(struct lbs_802_11d_domain_reg));
		generate_domain_info_11d(&priv->parsed_region_chan,
					 &priv->domainreg);

		ret = set_domain_info_11d(priv);

		if (ret) {
			lbs_deb_11d("error setting domain info\n");
			goto done;
		}

	}
	ret = 0;

done:
	lbs_deb_leave_args(LBS_DEB_11D, "ret %d", ret);
	return ret;
}