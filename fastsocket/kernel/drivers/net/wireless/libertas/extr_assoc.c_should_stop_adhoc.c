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
struct TYPE_2__ {scalar_t__ channel; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct lbs_private {scalar_t__ connect_status; TYPE_1__ curbssparams; } ;
struct assoc_request {scalar_t__ mode; scalar_t__ channel; int /*<<< orphan*/  flags; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_CHANNEL ; 
 int /*<<< orphan*/  ASSOC_FLAG_MODE ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ lbs_ssid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int should_stop_adhoc(struct lbs_private *priv,
                             struct assoc_request * assoc_req)
{
	lbs_deb_enter(LBS_DEB_ASSOC);

	if (priv->connect_status != LBS_CONNECTED)
		return 0;

	if (lbs_ssid_cmp(priv->curbssparams.ssid,
	                      priv->curbssparams.ssid_len,
	                      assoc_req->ssid, assoc_req->ssid_len) != 0)
		return 1;

	/* FIXME: deal with 'auto' mode somehow */
	if (test_bit(ASSOC_FLAG_MODE, &assoc_req->flags)) {
		if (assoc_req->mode != IW_MODE_ADHOC)
			return 1;
	}

	if (test_bit(ASSOC_FLAG_CHANNEL, &assoc_req->flags)) {
		if (assoc_req->channel != priv->curbssparams.channel)
			return 1;
	}

	lbs_deb_leave(LBS_DEB_ASSOC);
	return 0;
}