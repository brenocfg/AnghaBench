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
typedef  scalar_t__ uint8_t ;
struct region_channel {int nrcfp; scalar_t__ band; struct chan_freq_power* CFP; int /*<<< orphan*/  valid; } ;
struct lbs_private {scalar_t__ connect_status; scalar_t__ mesh_connect_status; int /*<<< orphan*/  parsed_region_chan; scalar_t__ enable11d; struct region_channel* region_channel; struct region_channel* universal_channel; } ;
struct TYPE_2__ {int passivescan; } ;
struct chanscanparamset {int /*<<< orphan*/  channumber; TYPE_1__ chanscanmode; void* maxscantime; int /*<<< orphan*/  radiotype; } ;
struct chan_freq_power {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct region_channel*) ; 
 scalar_t__ BAND_B ; 
 scalar_t__ BAND_G ; 
 int /*<<< orphan*/  CMD_SCAN_RADIO_TYPE_BG ; 
 scalar_t__ CMD_SCAN_TYPE_ACTIVE ; 
 scalar_t__ CMD_SCAN_TYPE_PASSIVE ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  MRVDRV_ACTIVE_SCAN_CHAN_TIME ; 
 int /*<<< orphan*/  MRVDRV_PASSIVE_SCAN_CHAN_TIME ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ lbs_get_scan_type_11d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int lbs_scan_create_channel_list(struct lbs_private *priv,
					struct chanscanparamset *scanchanlist)
{
	struct region_channel *scanregion;
	struct chan_freq_power *cfp;
	int rgnidx;
	int chanidx;
	int nextchan;
	uint8_t scantype;

	chanidx = 0;

	/* Set the default scan type to the user specified type, will later
	 *   be changed to passive on a per channel basis if restricted by
	 *   regulatory requirements (11d or 11h)
	 */
	scantype = CMD_SCAN_TYPE_ACTIVE;

	for (rgnidx = 0; rgnidx < ARRAY_SIZE(priv->region_channel); rgnidx++) {
		if (priv->enable11d && (priv->connect_status != LBS_CONNECTED)
		    && (priv->mesh_connect_status != LBS_CONNECTED)) {
			/* Scan all the supported chan for the first scan */
			if (!priv->universal_channel[rgnidx].valid)
				continue;
			scanregion = &priv->universal_channel[rgnidx];

			/* clear the parsed_region_chan for the first scan */
			memset(&priv->parsed_region_chan, 0x00,
			       sizeof(priv->parsed_region_chan));
		} else {
			if (!priv->region_channel[rgnidx].valid)
				continue;
			scanregion = &priv->region_channel[rgnidx];
		}

		for (nextchan = 0; nextchan < scanregion->nrcfp; nextchan++, chanidx++) {
			struct chanscanparamset *chan = &scanchanlist[chanidx];

			cfp = scanregion->CFP + nextchan;

			if (priv->enable11d)
				scantype = lbs_get_scan_type_11d(cfp->channel,
								 &priv->parsed_region_chan);

			if (scanregion->band == BAND_B || scanregion->band == BAND_G)
				chan->radiotype = CMD_SCAN_RADIO_TYPE_BG;

			if (scantype == CMD_SCAN_TYPE_PASSIVE) {
				chan->maxscantime = cpu_to_le16(MRVDRV_PASSIVE_SCAN_CHAN_TIME);
				chan->chanscanmode.passivescan = 1;
			} else {
				chan->maxscantime = cpu_to_le16(MRVDRV_ACTIVE_SCAN_CHAN_TIME);
				chan->chanscanmode.passivescan = 0;
			}

			chan->channumber = cfp->channel;
		}
	}
	return chanidx;
}