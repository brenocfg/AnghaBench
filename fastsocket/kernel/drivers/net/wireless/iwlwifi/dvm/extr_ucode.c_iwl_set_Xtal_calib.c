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
struct iwl_priv {TYPE_1__* nvm_data; } ;
struct iwl_calib_xtal_freq_cmd {void* cap_pin2; void* cap_pin1; int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/ * xtal_calib; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_PHY_CALIBRATE_CRYSTAL_FRQ_CMD ; 
 int iwl_calib_set (struct iwl_priv*,void*,int) ; 
 int /*<<< orphan*/  iwl_set_calib_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_set_Xtal_calib(struct iwl_priv *priv)
{
	struct iwl_calib_xtal_freq_cmd cmd;
	__le16 *xtal_calib = priv->nvm_data->xtal_calib;

	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_CRYSTAL_FRQ_CMD);
	cmd.cap_pin1 = le16_to_cpu(xtal_calib[0]);
	cmd.cap_pin2 = le16_to_cpu(xtal_calib[1]);
	return iwl_calib_set(priv, (void *)&cmd, sizeof(cmd));
}