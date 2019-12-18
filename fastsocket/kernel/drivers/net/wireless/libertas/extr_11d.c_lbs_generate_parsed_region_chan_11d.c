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
struct region_channel {size_t nrcfp; int /*<<< orphan*/  region; int /*<<< orphan*/  band; struct chan_freq_power* CFP; } ;
struct parsed_region_chan_11d {size_t nr_chan; TYPE_1__* chanpwr; int /*<<< orphan*/  band; int /*<<< orphan*/  region; int /*<<< orphan*/  countrycode; } ;
struct chan_freq_power {int /*<<< orphan*/  maxtxpower; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwr; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTRY_CODE_LEN ; 
 int /*<<< orphan*/  lbs_code_2_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_11d (char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lbs_generate_parsed_region_chan_11d(struct region_channel *region_chan,
					  struct parsed_region_chan_11d *
					  parsed_region_chan)
{
	u8 i;
	struct chan_freq_power *cfp;

	if (region_chan == NULL) {
		lbs_deb_11d("region_chan is NULL\n");
		return;
	}

	cfp = region_chan->CFP;
	if (cfp == NULL) {
		lbs_deb_11d("cfp is NULL \n");
		return;
	}

	parsed_region_chan->band = region_chan->band;
	parsed_region_chan->region = region_chan->region;
	memcpy(parsed_region_chan->countrycode,
	       lbs_code_2_region(region_chan->region), COUNTRY_CODE_LEN);

	lbs_deb_11d("region 0x%x, band %d\n", parsed_region_chan->region,
	       parsed_region_chan->band);

	for (i = 0; i < region_chan->nrcfp; i++, cfp++) {
		parsed_region_chan->chanpwr[i].chan = cfp->channel;
		parsed_region_chan->chanpwr[i].pwr = cfp->maxtxpower;
		lbs_deb_11d("chan %d, pwr %d\n",
		       parsed_region_chan->chanpwr[i].chan,
		       parsed_region_chan->chanpwr[i].pwr);
	}
	parsed_region_chan->nr_chan = region_chan->nrcfp;

	lbs_deb_11d("nrchan %d\n", parsed_region_chan->nr_chan);

	return;
}