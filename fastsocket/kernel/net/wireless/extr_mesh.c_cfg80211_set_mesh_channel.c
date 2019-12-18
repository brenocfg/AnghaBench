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
struct cfg80211_chan_def {scalar_t__ width; int /*<<< orphan*/  chan; } ;
struct wireless_dev {struct cfg80211_chan_def preset_chandef; scalar_t__ mesh_id_len; int /*<<< orphan*/  channel; int /*<<< orphan*/  netdev; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ libertas_set_mesh_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_MODE_SHARED ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENETDOWN ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int cfg80211_can_use_chan (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int rdev_libertas_set_mesh_channel (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cfg80211_set_mesh_channel(struct cfg80211_registered_device *rdev,
			      struct wireless_dev *wdev,
			      struct cfg80211_chan_def *chandef)
{
	int err;

	/*
	 * Workaround for libertas (only!), it puts the interface
	 * into mesh mode but doesn't implement join_mesh. Instead,
	 * it is configured via sysfs and then joins the mesh when
	 * you set the channel. Note that the libertas mesh isn't
	 * compatible with 802.11 mesh.
	 */
	if (rdev->ops->libertas_set_mesh_channel) {
		if (chandef->width != NL80211_CHAN_WIDTH_20_NOHT)
			return -EINVAL;

		if (!netif_running(wdev->netdev))
			return -ENETDOWN;

		err = cfg80211_can_use_chan(rdev, wdev, chandef->chan,
					    CHAN_MODE_SHARED);
		if (err)
			return err;

		err = rdev_libertas_set_mesh_channel(rdev, wdev->netdev,
						     chandef->chan);
		if (!err)
			wdev->channel = chandef->chan;

		return err;
	}

	if (wdev->mesh_id_len)
		return -EBUSY;

	wdev->preset_chandef = *chandef;
	return 0;
}