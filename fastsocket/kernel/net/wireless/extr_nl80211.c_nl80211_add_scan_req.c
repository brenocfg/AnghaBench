#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct cfg80211_scan_request {int n_ssids; int n_channels; scalar_t__ flags; scalar_t__ ie; int /*<<< orphan*/  ie_len; TYPE_2__** channels; TYPE_1__* ssids; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  sched_scan_mtx; struct cfg80211_scan_request* scan_req; } ;
struct TYPE_4__ {scalar_t__ center_freq; } ;
struct TYPE_3__ {scalar_t__ ssid; int /*<<< orphan*/  ssid_len; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int NL80211_ATTR_IE ; 
 int NL80211_ATTR_SCAN_FLAGS ; 
 int /*<<< orphan*/  NL80211_ATTR_SCAN_FREQUENCIES ; 
 int /*<<< orphan*/  NL80211_ATTR_SCAN_SSIDS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,scalar_t__) ; 

__attribute__((used)) static int nl80211_add_scan_req(struct sk_buff *msg,
				struct cfg80211_registered_device *rdev)
{
	struct cfg80211_scan_request *req = rdev->scan_req;
	struct nlattr *nest;
	int i;

	lockdep_assert_held(&rdev->sched_scan_mtx);

	if (WARN_ON(!req))
		return 0;

	nest = nla_nest_start(msg, NL80211_ATTR_SCAN_SSIDS);
	if (!nest)
		goto nla_put_failure;
	for (i = 0; i < req->n_ssids; i++) {
		if (nla_put(msg, i, req->ssids[i].ssid_len, req->ssids[i].ssid))
			goto nla_put_failure;
	}
	nla_nest_end(msg, nest);

	nest = nla_nest_start(msg, NL80211_ATTR_SCAN_FREQUENCIES);
	if (!nest)
		goto nla_put_failure;
	for (i = 0; i < req->n_channels; i++) {
		if (nla_put_u32(msg, i, req->channels[i]->center_freq))
			goto nla_put_failure;
	}
	nla_nest_end(msg, nest);

	if (req->ie &&
	    nla_put(msg, NL80211_ATTR_IE, req->ie_len, req->ie))
		goto nla_put_failure;

	if (req->flags)
		nla_put_u32(msg, NL80211_ATTR_SCAN_FLAGS, req->flags);

	return 0;
 nla_put_failure:
	return -ENOBUFS;
}