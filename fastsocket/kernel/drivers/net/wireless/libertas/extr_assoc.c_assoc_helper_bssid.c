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
struct bss_descriptor {int dummy; } ;
struct assoc_request {int bssid; scalar_t__ mode; int /*<<< orphan*/  bss; } ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  lbs_adhoc_join (struct lbs_private*,struct assoc_request*) ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,int) ; 
 int /*<<< orphan*/  lbs_deb_enter_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 struct bss_descriptor* lbs_find_bssid_in_list (struct lbs_private*,int,scalar_t__) ; 
 int lbs_try_associate (struct lbs_private*,struct assoc_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct bss_descriptor*,int) ; 

__attribute__((used)) static int assoc_helper_bssid(struct lbs_private *priv,
                              struct assoc_request * assoc_req)
{
	int ret = 0;
	struct bss_descriptor * bss;

	lbs_deb_enter_args(LBS_DEB_ASSOC, "BSSID %pM", assoc_req->bssid);

	/* Search for index position in list for requested MAC */
	bss = lbs_find_bssid_in_list(priv, assoc_req->bssid,
			    assoc_req->mode);
	if (bss == NULL) {
		lbs_deb_assoc("ASSOC: WAP: BSSID %pM not found, "
			"cannot associate.\n", assoc_req->bssid);
		goto out;
	}

	memcpy(&assoc_req->bss, bss, sizeof(struct bss_descriptor));
	if (assoc_req->mode == IW_MODE_INFRA) {
		ret = lbs_try_associate(priv, assoc_req);
		lbs_deb_assoc("ASSOC: lbs_try_associate(bssid) returned %d\n",
			      ret);
	} else if (assoc_req->mode == IW_MODE_ADHOC) {
		lbs_adhoc_join(priv, assoc_req);
	}

out:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}