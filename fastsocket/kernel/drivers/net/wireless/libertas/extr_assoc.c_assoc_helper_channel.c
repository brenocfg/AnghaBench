#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ channel; } ;
struct lbs_private {TYPE_3__ curbssparams; scalar_t__ mesh_dev; } ;
struct TYPE_4__ {scalar_t__ wep_enabled; } ;
struct assoc_request {scalar_t__ channel; int /*<<< orphan*/  flags; TYPE_2__* wep_keys; TYPE_1__ secinfo; } ;
struct TYPE_5__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_SSID ; 
 int /*<<< orphan*/  ASSOC_FLAG_WEP_KEYS ; 
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_START ; 
 int /*<<< orphan*/  CMD_ACT_MESH_CONFIG_STOP ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_mesh_config (struct lbs_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int lbs_set_channel (struct lbs_private*,scalar_t__) ; 
 int lbs_update_channel (struct lbs_private*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int assoc_helper_channel(struct lbs_private *priv,
                                struct assoc_request * assoc_req)
{
	int ret = 0;

	lbs_deb_enter(LBS_DEB_ASSOC);

	ret = lbs_update_channel(priv);
	if (ret) {
		lbs_deb_assoc("ASSOC: channel: error getting channel.\n");
		goto done;
	}

	if (assoc_req->channel == priv->curbssparams.channel)
		goto done;

	if (priv->mesh_dev) {
		/* Change mesh channel first; 21.p21 firmware won't let
		   you change channel otherwise (even though it'll return
		   an error to this */
		lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_STOP,
				assoc_req->channel);
	}

	lbs_deb_assoc("ASSOC: channel: %d -> %d\n",
		      priv->curbssparams.channel, assoc_req->channel);

	ret = lbs_set_channel(priv, assoc_req->channel);
	if (ret < 0)
		lbs_deb_assoc("ASSOC: channel: error setting channel.\n");

	/* FIXME: shouldn't need to grab the channel _again_ after setting
	 * it since the firmware is supposed to return the new channel, but
	 * whatever... */
	ret = lbs_update_channel(priv);
	if (ret) {
		lbs_deb_assoc("ASSOC: channel: error getting channel.\n");
		goto done;
	}

	if (assoc_req->channel != priv->curbssparams.channel) {
		lbs_deb_assoc("ASSOC: channel: failed to update channel to %d\n",
		              assoc_req->channel);
		goto restore_mesh;
	}

	if (   assoc_req->secinfo.wep_enabled
	    &&   (assoc_req->wep_keys[0].len
	       || assoc_req->wep_keys[1].len
	       || assoc_req->wep_keys[2].len
	       || assoc_req->wep_keys[3].len)) {
		/* Make sure WEP keys are re-sent to firmware */
		set_bit(ASSOC_FLAG_WEP_KEYS, &assoc_req->flags);
	}

	/* Must restart/rejoin adhoc networks after channel change */
 	set_bit(ASSOC_FLAG_SSID, &assoc_req->flags);

 restore_mesh:
	if (priv->mesh_dev)
		lbs_mesh_config(priv, CMD_ACT_MESH_CONFIG_START,
				priv->curbssparams.channel);

 done:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}