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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_priv {int /*<<< orphan*/  notif_wait; } ;
struct iwl_notification_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CALIBRATION_COMPLETE_NOTIFICATION 128 
 int HZ ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int) ; 
 int iwl_init_alive_start (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int) ; 

__attribute__((used)) static int iwl_testmode_cfg_init_calib(struct iwl_priv *priv)
{
	struct iwl_notification_wait calib_wait;
	static const u8 calib_complete[] = {
		CALIBRATION_COMPLETE_NOTIFICATION
	};
	int ret;

	iwl_init_notification_wait(&priv->notif_wait, &calib_wait,
				   calib_complete, ARRAY_SIZE(calib_complete),
				   NULL, NULL);
	ret = iwl_init_alive_start(priv);
	if (ret) {
		IWL_ERR(priv, "Fail init calibration: %d\n", ret);
		goto cfg_init_calib_error;
	}

	ret = iwl_wait_notification(&priv->notif_wait, &calib_wait, 2 * HZ);
	if (ret)
		IWL_ERR(priv, "Error detecting"
			" CALIBRATION_COMPLETE_NOTIFICATION: %d\n", ret);
	return ret;

cfg_init_calib_error:
	iwl_remove_notification(&priv->notif_wait, &calib_wait);
	return ret;
}