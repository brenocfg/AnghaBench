#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int /*<<< orphan*/  netdev; TYPE_3__* conn; TYPE_4__* wiphy; } ;
struct ieee80211_supported_band {int n_channels; int n_bitrates; struct ieee80211_channel* channels; } ;
struct ieee80211_channel {int flags; } ;
struct cfg80211_scan_request {int* rates; int n_channels; int n_ssids; int /*<<< orphan*/  scan_start; int /*<<< orphan*/ * wiphy; struct wireless_dev* wdev; TYPE_1__* ssids; struct ieee80211_channel** channels; } ;
struct cfg80211_registered_device {struct cfg80211_scan_request* scan_req; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  sched_scan_mtx; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_8__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_6__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; struct ieee80211_channel* channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; TYPE_2__ params; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RDEV_LOCK (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  CFG80211_CONN_SCANNING ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_NUM_BANDS ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct cfg80211_scan_request*) ; 
 struct cfg80211_scan_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_send_scan_start (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int rdev_scan (struct cfg80211_registered_device*,struct cfg80211_scan_request*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (TYPE_4__*) ; 

__attribute__((used)) static int cfg80211_conn_scan(struct wireless_dev *wdev)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	struct cfg80211_scan_request *request;
	int n_channels, err;

	ASSERT_RTNL();
	ASSERT_RDEV_LOCK(rdev);
	ASSERT_WDEV_LOCK(wdev);
	lockdep_assert_held(&rdev->sched_scan_mtx);

	if (rdev->scan_req)
		return -EBUSY;

	if (wdev->conn->params.channel) {
		n_channels = 1;
	} else {
		enum ieee80211_band band;
		n_channels = 0;

		for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
			if (!wdev->wiphy->bands[band])
				continue;
			n_channels += wdev->wiphy->bands[band]->n_channels;
		}
	}
	request = kzalloc(sizeof(*request) + sizeof(request->ssids[0]) +
			  sizeof(request->channels[0]) * n_channels,
			  GFP_KERNEL);
	if (!request)
		return -ENOMEM;

	if (wdev->conn->params.channel)
		request->channels[0] = wdev->conn->params.channel;
	else {
		int i = 0, j;
		enum ieee80211_band band;
		struct ieee80211_supported_band *bands;
		struct ieee80211_channel *channel;

		for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
			bands = wdev->wiphy->bands[band];
			if (!bands)
				continue;
			for (j = 0; j < bands->n_channels; j++) {
				channel = &bands->channels[j];
				if (channel->flags & IEEE80211_CHAN_DISABLED)
					continue;
				request->channels[i++] = channel;
			}
			request->rates[band] = (1 << bands->n_bitrates) - 1;
		}
		n_channels = i;
	}
	request->n_channels = n_channels;
	request->ssids = (void *)&request->channels[n_channels];
	request->n_ssids = 1;

	memcpy(request->ssids[0].ssid, wdev->conn->params.ssid,
		wdev->conn->params.ssid_len);
	request->ssids[0].ssid_len = wdev->conn->params.ssid_len;

	request->wdev = wdev;
	request->wiphy = &rdev->wiphy;
	request->scan_start = jiffies;

	rdev->scan_req = request;

	err = rdev_scan(rdev, request);
	if (!err) {
		wdev->conn->state = CFG80211_CONN_SCANNING;
		nl80211_send_scan_start(rdev, wdev);
		dev_hold(wdev->netdev);
	} else {
		rdev->scan_req = NULL;
		kfree(request);
	}
	return err;
}