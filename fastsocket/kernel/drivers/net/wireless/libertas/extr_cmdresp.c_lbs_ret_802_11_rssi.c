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
struct lbs_private {int** SNR; int** NF; void*** RSSI; } ;
struct cmd_ds_802_11_rssi_rsp {int /*<<< orphan*/  avgnoisefloor; int /*<<< orphan*/  avgSNR; int /*<<< orphan*/  noisefloor; int /*<<< orphan*/  SNR; } ;
struct TYPE_2__ {struct cmd_ds_802_11_rssi_rsp rssirsp; } ;
struct cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int AVG_SCALE ; 
 void* CAL_RSSI (int,int) ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 size_t TYPE_AVG ; 
 size_t TYPE_BEACON ; 
 size_t TYPE_NOAVG ; 
 void* get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,void*,void*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_ret_802_11_rssi(struct lbs_private *priv,
				struct cmd_ds_command *resp)
{
	struct cmd_ds_802_11_rssi_rsp *rssirsp = &resp->params.rssirsp;

	lbs_deb_enter(LBS_DEB_CMD);

	/* store the non average value */
	priv->SNR[TYPE_BEACON][TYPE_NOAVG] = get_unaligned_le16(&rssirsp->SNR);
	priv->NF[TYPE_BEACON][TYPE_NOAVG] = get_unaligned_le16(&rssirsp->noisefloor);

	priv->SNR[TYPE_BEACON][TYPE_AVG] = get_unaligned_le16(&rssirsp->avgSNR);
	priv->NF[TYPE_BEACON][TYPE_AVG] = get_unaligned_le16(&rssirsp->avgnoisefloor);

	priv->RSSI[TYPE_BEACON][TYPE_NOAVG] =
	    CAL_RSSI(priv->SNR[TYPE_BEACON][TYPE_NOAVG],
		     priv->NF[TYPE_BEACON][TYPE_NOAVG]);

	priv->RSSI[TYPE_BEACON][TYPE_AVG] =
	    CAL_RSSI(priv->SNR[TYPE_BEACON][TYPE_AVG] / AVG_SCALE,
		     priv->NF[TYPE_BEACON][TYPE_AVG] / AVG_SCALE);

	lbs_deb_cmd("RSSI: beacon %d, avg %d\n",
	       priv->RSSI[TYPE_BEACON][TYPE_NOAVG],
	       priv->RSSI[TYPE_BEACON][TYPE_AVG]);

	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}