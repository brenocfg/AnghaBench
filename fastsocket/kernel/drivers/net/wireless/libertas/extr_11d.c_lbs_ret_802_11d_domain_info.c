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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int len; } ;
struct mrvl_ie_domain_param_set {TYPE_1__ header; } ;
struct ieee_subbandset {int dummy; } ;
struct cmd_ds_802_11d_domain_info {int action; struct mrvl_ie_domain_param_set domain; } ;
struct TYPE_4__ {struct cmd_ds_802_11d_domain_info domaininforesp; } ;
struct cmd_ds_command {int size; TYPE_2__ params; } ;
typedef  int s16 ;

/* Variables and functions */
#define  CMD_ACT_GET 129 
#define  CMD_ACT_SET 128 
 int COUNTRY_CODE_LEN ; 
 int /*<<< orphan*/  LBS_DEB_11D ; 
 int MRVDRV_MAX_SUBBAND_802_11D ; 
 int /*<<< orphan*/  lbs_deb_11d (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int le16_to_cpu (int) ; 

int lbs_ret_802_11d_domain_info(struct cmd_ds_command *resp)
{
	struct cmd_ds_802_11d_domain_info *domaininfo = &resp->params.domaininforesp;
	struct mrvl_ie_domain_param_set *domain = &domaininfo->domain;
	u16 action = le16_to_cpu(domaininfo->action);
	s16 ret = 0;
	u8 nr_subband = 0;

	lbs_deb_enter(LBS_DEB_11D);

	lbs_deb_hex(LBS_DEB_11D, "domain info resp", (u8 *) resp,
		(int)le16_to_cpu(resp->size));

	nr_subband = (le16_to_cpu(domain->header.len) - COUNTRY_CODE_LEN) /
		      sizeof(struct ieee_subbandset);

	lbs_deb_11d("domain info resp: nr_subband %d\n", nr_subband);

	if (nr_subband > MRVDRV_MAX_SUBBAND_802_11D) {
		lbs_deb_11d("Invalid Numrer of Subband returned!!\n");
		return -1;
	}

	switch (action) {
	case CMD_ACT_SET:	/*Proc Set action */
		break;

	case CMD_ACT_GET:
		break;
	default:
		lbs_deb_11d("Invalid action:%d\n", domaininfo->action);
		ret = -1;
		break;
	}

	lbs_deb_leave_args(LBS_DEB_11D, "ret %d", ret);
	return ret;
}