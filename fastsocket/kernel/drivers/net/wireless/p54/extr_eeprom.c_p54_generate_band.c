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
struct p54_common {struct ieee80211_supported_band** band_table; TYPE_1__* survey; } ;
struct p54_channel_list {unsigned int entries; int* band_channel_num; struct p54_channel_entry* channels; } ;
struct p54_channel_entry {int band; int data; int /*<<< orphan*/  max_power; int /*<<< orphan*/  freq; int /*<<< orphan*/  index; } ;
struct ieee80211_supported_band {int band; unsigned int hw_value; unsigned int n_channels; struct ieee80211_supported_band* channels; int /*<<< orphan*/  max_power; int /*<<< orphan*/  center_freq; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct p54_common* priv; } ;
struct ieee80211_channel {int band; unsigned int hw_value; unsigned int n_channels; struct ieee80211_channel* channels; int /*<<< orphan*/  max_power; int /*<<< orphan*/  center_freq; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_2__ {int filled; struct ieee80211_supported_band* channel; } ;

/* Variables and functions */
 int CHAN_HAS_ALL ; 
 int CHAN_HAS_CAL ; 
 int CHAN_HAS_CURVE ; 
 int CHAN_HAS_LIMIT ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_BAND_2GHZ ; 
 int SURVEY_INFO_CHANNEL_TIME ; 
 int SURVEY_INFO_CHANNEL_TIME_BUSY ; 
 int SURVEY_INFO_CHANNEL_TIME_TX ; 
 int SURVEY_INFO_NOISE_DBM ; 
 int /*<<< orphan*/  kfree (struct ieee80211_supported_band*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int p54_fill_band_bitrates (struct ieee80211_hw*,struct ieee80211_supported_band*,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int p54_generate_band(struct ieee80211_hw *dev,
			     struct p54_channel_list *list,
			     unsigned int *chan_num,
			     enum ieee80211_band band)
{
	struct p54_common *priv = dev->priv;
	struct ieee80211_supported_band *tmp, *old;
	unsigned int i, j;
	int ret = -ENOMEM;

	if ((!list->entries) || (!list->band_channel_num[band]))
		return -EINVAL;

	tmp = kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		goto err_out;

	tmp->channels = kzalloc(sizeof(struct ieee80211_channel) *
				list->band_channel_num[band], GFP_KERNEL);
	if (!tmp->channels)
		goto err_out;

	ret = p54_fill_band_bitrates(dev, tmp, band);
	if (ret)
		goto err_out;

	for (i = 0, j = 0; (j < list->band_channel_num[band]) &&
			   (i < list->entries); i++) {
		struct p54_channel_entry *chan = &list->channels[i];
		struct ieee80211_channel *dest = &tmp->channels[j];

		if (chan->band != band)
			continue;

		if (chan->data != CHAN_HAS_ALL) {
			wiphy_err(dev->wiphy, "%s%s%s is/are missing for "
				  "channel:%d [%d MHz].\n",
				  (chan->data & CHAN_HAS_CAL ? "" :
				   " [iqauto calibration data]"),
				  (chan->data & CHAN_HAS_LIMIT ? "" :
				   " [output power limits]"),
				  (chan->data & CHAN_HAS_CURVE ? "" :
				   " [curve data]"),
				  chan->index, chan->freq);
			continue;
		}

		dest->band = chan->band;
		dest->center_freq = chan->freq;
		dest->max_power = chan->max_power;
		priv->survey[*chan_num].channel = &tmp->channels[j];
		priv->survey[*chan_num].filled = SURVEY_INFO_NOISE_DBM |
			SURVEY_INFO_CHANNEL_TIME |
			SURVEY_INFO_CHANNEL_TIME_BUSY |
			SURVEY_INFO_CHANNEL_TIME_TX;
		dest->hw_value = (*chan_num);
		j++;
		(*chan_num)++;
	}

	if (j == 0) {
		wiphy_err(dev->wiphy, "Disabling totally damaged %d GHz band\n",
			  (band == IEEE80211_BAND_2GHZ) ? 2 : 5);

		ret = -ENODATA;
		goto err_out;
	}

	tmp->n_channels = j;
	old = priv->band_table[band];
	priv->band_table[band] = tmp;
	if (old) {
		kfree(old->channels);
		kfree(old);
	}

	return 0;

err_out:
	if (tmp) {
		kfree(tmp->channels);
		kfree(tmp);
	}

	return ret;
}