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
struct lbs_private {int dummy; } ;
struct assoc_request {int /*<<< orphan*/  flags; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_BSSID ; 
 int /*<<< orphan*/  ASSOC_FLAG_SSID ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int assoc_helper_bssid (struct lbs_private*,struct assoc_request*) ; 
 int assoc_helper_essid (struct lbs_private*,struct assoc_request*) ; 
 int /*<<< orphan*/  bssid_any ; 
 int /*<<< orphan*/  bssid_off ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int assoc_helper_associate(struct lbs_private *priv,
                                  struct assoc_request * assoc_req)
{
	int ret = 0, done = 0;

	lbs_deb_enter(LBS_DEB_ASSOC);

	/* If we're given and 'any' BSSID, try associating based on SSID */

	if (test_bit(ASSOC_FLAG_BSSID, &assoc_req->flags)) {
		if (compare_ether_addr(bssid_any, assoc_req->bssid)
		    && compare_ether_addr(bssid_off, assoc_req->bssid)) {
			ret = assoc_helper_bssid(priv, assoc_req);
			done = 1;
		}
	}

	if (!done && test_bit(ASSOC_FLAG_SSID, &assoc_req->flags)) {
		ret = assoc_helper_essid(priv, assoc_req);
	}

	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}