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
struct parsed_region_chan_11d {int dummy; } ;
struct lbs_private {int /*<<< orphan*/  domainreg; int /*<<< orphan*/  parsed_region_chan; scalar_t__ enable11d; } ;
struct lbs_802_11d_domain_reg {int dummy; } ;
struct bss_descriptor {int /*<<< orphan*/  countryinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_11D ; 
 int /*<<< orphan*/  generate_domain_info_11d (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_11d (char*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int parse_domain_info_11d (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_domain_info_11d (struct lbs_private*) ; 

int lbs_parse_dnld_countryinfo_11d(struct lbs_private *priv,
                                        struct bss_descriptor * bss)
{
	int ret;

	lbs_deb_enter(LBS_DEB_11D);
	if (priv->enable11d) {
		memset(&priv->parsed_region_chan, 0,
		       sizeof(struct parsed_region_chan_11d));
		ret = parse_domain_info_11d(&bss->countryinfo, 0,
					       &priv->parsed_region_chan);

		if (ret == -1) {
			lbs_deb_11d("error parsing domain_info from AP\n");
			goto done;
		}

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