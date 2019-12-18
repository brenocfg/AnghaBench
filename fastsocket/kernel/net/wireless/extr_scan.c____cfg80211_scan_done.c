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
typedef  int /*<<< orphan*/  wrqu ;
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct wireless_dev {scalar_t__ netdev; } ;
struct cfg80211_scan_request {int flags; scalar_t__ aborted; int /*<<< orphan*/  scan_start; struct wireless_dev* wdev; } ;
struct cfg80211_registered_device {struct cfg80211_scan_request* scan_req; int /*<<< orphan*/  bss_lock; int /*<<< orphan*/  sched_scan_mtx; } ;

/* Variables and functions */
 int NL80211_SCAN_FLAG_FLUSH ; 
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  __cfg80211_bss_expire (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_sme_scan_done (scalar_t__) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_scan_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_send_scan_aborted (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  nl80211_send_scan_done (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireless_send_event (scalar_t__,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void ___cfg80211_scan_done(struct cfg80211_registered_device *rdev, bool leak)
{
	struct cfg80211_scan_request *request;
	struct wireless_dev *wdev;
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
#endif

	lockdep_assert_held(&rdev->sched_scan_mtx);

	request = rdev->scan_req;

	if (!request)
		return;

	wdev = request->wdev;

	/*
	 * This must be before sending the other events!
	 * Otherwise, wpa_supplicant gets completely confused with
	 * wext events.
	 */
	if (wdev->netdev)
		cfg80211_sme_scan_done(wdev->netdev);

	if (request->aborted) {
		nl80211_send_scan_aborted(rdev, wdev);
	} else {
		if (request->flags & NL80211_SCAN_FLAG_FLUSH) {
			/* flush entries from previous scans */
			spin_lock_bh(&rdev->bss_lock);
			__cfg80211_bss_expire(rdev, request->scan_start);
			spin_unlock_bh(&rdev->bss_lock);
		}
		nl80211_send_scan_done(rdev, wdev);
	}

#ifdef CONFIG_CFG80211_WEXT
	if (wdev->netdev && !request->aborted) {
		memset(&wrqu, 0, sizeof(wrqu));

		wireless_send_event(wdev->netdev, SIOCGIWSCAN, &wrqu, NULL);
	}
#endif

	if (wdev->netdev)
		dev_put(wdev->netdev);

	rdev->scan_req = NULL;

	/*
	 * OK. If this is invoked with "leak" then we can't
	 * free this ... but we've cleaned it up anyway. The
	 * driver failed to call the scan_done callback, so
	 * all bets are off, it might still be trying to use
	 * the scan request or not ... if it accesses the dev
	 * in there (it shouldn't anyway) then it may crash.
	 */
	if (!leak)
		kfree(request);
}