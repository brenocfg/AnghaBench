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
struct wl12xx_priv {int /*<<< orphan*/  ref_clock; } ;
struct wl1271_ini_general_params {scalar_t__ tx_bip_fem_manufacturer; } ;
struct wl1271_nvs_file {struct wl1271_ini_general_params general_params; } ;
struct TYPE_4__ {int tx_bip_fem_auto_detect; scalar_t__ tx_bip_fem_manufacturer; int /*<<< orphan*/  ref_clock; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct wl1271_general_parms_cmd {TYPE_2__ general_params; TYPE_1__ test; } ;
struct wl1271 {scalar_t__ plt_mode; scalar_t__ fem_manuf; scalar_t__ nvs; struct wl12xx_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PLT_FEM_DETECT ; 
 int /*<<< orphan*/  TEST_CMD_INI_FILE_GENERAL_PARAM ; 
 scalar_t__ WL1271_INI_FEM_MODULE_COUNT ; 
 int /*<<< orphan*/  kfree (struct wl1271_general_parms_cmd*) ; 
 struct wl1271_general_parms_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct wl1271_ini_general_params*,int) ; 
 int wl1271_cmd_test (struct wl1271*,struct wl1271_general_parms_cmd*,int,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_cmd_general_parms(struct wl1271 *wl)
{
	struct wl1271_general_parms_cmd *gen_parms;
	struct wl1271_ini_general_params *gp =
		&((struct wl1271_nvs_file *)wl->nvs)->general_params;
	struct wl12xx_priv *priv = wl->priv;
	bool answer = false;
	int ret;

	if (!wl->nvs)
		return -ENODEV;

	if (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) {
		wl1271_warning("FEM index from INI out of bounds");
		return -EINVAL;
	}

	gen_parms = kzalloc(sizeof(*gen_parms), GFP_KERNEL);
	if (!gen_parms)
		return -ENOMEM;

	gen_parms->test.id = TEST_CMD_INI_FILE_GENERAL_PARAM;

	memcpy(&gen_parms->general_params, gp, sizeof(*gp));

	/* If we started in PLT FEM_DETECT mode, force auto detect */
	if (wl->plt_mode == PLT_FEM_DETECT)
		gen_parms->general_params.tx_bip_fem_auto_detect = true;

	if (gen_parms->general_params.tx_bip_fem_auto_detect)
		answer = true;

	/* Override the REF CLK from the NVS with the one from platform data */
	gen_parms->general_params.ref_clock = priv->ref_clock;

	ret = wl1271_cmd_test(wl, gen_parms, sizeof(*gen_parms), answer);
	if (ret < 0) {
		wl1271_warning("CMD_INI_FILE_GENERAL_PARAM failed");
		goto out;
	}

	gp->tx_bip_fem_manufacturer =
		gen_parms->general_params.tx_bip_fem_manufacturer;

	if (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) {
		wl1271_warning("FEM index from FW out of bounds");
		ret = -EINVAL;
		goto out;
	}

	/* If we are in calibrator based fem auto detect - save fem nr */
	if (wl->plt_mode == PLT_FEM_DETECT)
		wl->fem_manuf = gp->tx_bip_fem_manufacturer;

	wl1271_debug(DEBUG_CMD, "FEM autodetect: %s, manufacturer: %d\n",
		answer == false ?
			"manual" :
		wl->plt_mode == PLT_FEM_DETECT ?
			"calibrator_fem_detect" :
			"auto",
		gp->tx_bip_fem_manufacturer);

out:
	kfree(gen_parms);
	return ret;
}