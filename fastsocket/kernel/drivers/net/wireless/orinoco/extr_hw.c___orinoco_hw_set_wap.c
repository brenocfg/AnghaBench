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
struct hermes {int dummy; } ;
struct orinoco_private {int firmware_type; int /*<<< orphan*/  desired_bssid; int /*<<< orphan*/  bssid_fixed; struct hermes hw; } ;

/* Variables and functions */
#define  FIRMWARE_TYPE_AGERE 130 
#define  FIRMWARE_TYPE_INTERSIL 129 
#define  FIRMWARE_TYPE_SYMBOL 128 
 int /*<<< orphan*/  HERMES_RID_CNFMANDATORYBSSID_SYMBOL ; 
 int /*<<< orphan*/  HERMES_RID_CNFROAMINGMODE ; 
 int HERMES_WRITE_RECORD (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USER_BAP ; 
 int hermes_write_wordrec (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int __orinoco_hw_set_wap(struct orinoco_private *priv)
{
	int roaming_flag;
	int err = 0;
	struct hermes *hw = &priv->hw;

	switch (priv->firmware_type) {
	case FIRMWARE_TYPE_AGERE:
		/* not supported */
		break;
	case FIRMWARE_TYPE_INTERSIL:
		if (priv->bssid_fixed)
			roaming_flag = 2;
		else
			roaming_flag = 1;

		err = hermes_write_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFROAMINGMODE,
					   roaming_flag);
		break;
	case FIRMWARE_TYPE_SYMBOL:
		err = HERMES_WRITE_RECORD(hw, USER_BAP,
					  HERMES_RID_CNFMANDATORYBSSID_SYMBOL,
					  &priv->desired_bssid);
		break;
	}
	return err;
}