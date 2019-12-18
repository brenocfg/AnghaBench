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
struct lbs_private {scalar_t__ mode; scalar_t__ psstate; int /*<<< orphan*/  psmode; } ;
struct assoc_request {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_OPTION_WAITFORRSP ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LBS802_11POWERMODECAM ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  SNMP_MIB_OID_BSS_TYPE ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_ps_wakeup (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int lbs_set_snmp_mib (struct lbs_private*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int assoc_helper_mode(struct lbs_private *priv,
                             struct assoc_request * assoc_req)
{
	int ret = 0;

	lbs_deb_enter(LBS_DEB_ASSOC);

	if (assoc_req->mode == priv->mode)
		goto done;

	if (assoc_req->mode == IW_MODE_INFRA) {
		if (priv->psstate != PS_STATE_FULL_POWER)
			lbs_ps_wakeup(priv, CMD_OPTION_WAITFORRSP);
		priv->psmode = LBS802_11POWERMODECAM;
	}

	priv->mode = assoc_req->mode;
	ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_BSS_TYPE, assoc_req->mode);

done:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}