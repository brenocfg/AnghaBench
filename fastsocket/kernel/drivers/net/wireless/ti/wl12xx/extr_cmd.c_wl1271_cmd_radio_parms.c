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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct wl1271_radio_parms_cmd {int /*<<< orphan*/  dyn_params_5; int /*<<< orphan*/  static_params_5; int /*<<< orphan*/  dyn_params_2; int /*<<< orphan*/  static_params_2; TYPE_1__ test; } ;
struct wl1271_ini_general_params {int /*<<< orphan*/  tx_bip_fem_manufacturer; } ;
struct wl1271_nvs_file {TYPE_3__* dyn_radio_params_5; int /*<<< orphan*/  stat_radio_params_5; TYPE_2__* dyn_radio_params_2; int /*<<< orphan*/  stat_radio_params_2; struct wl1271_ini_general_params general_params; } ;
struct wl1271_ini_fem_params_5 {int dummy; } ;
struct wl1271_ini_fem_params_2 {int dummy; } ;
struct wl1271_ini_band_params_5 {int dummy; } ;
struct wl1271_ini_band_params_2 {int dummy; } ;
struct wl1271 {scalar_t__ nvs; } ;
struct TYPE_6__ {int /*<<< orphan*/  params; } ;
struct TYPE_5__ {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TEST_CMD_INI_FILE_RADIO_PARAM ; 
 int WL12XX_FEM_TO_NVS_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wl1271_radio_parms_cmd*) ; 
 struct wl1271_radio_parms_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int wl1271_cmd_test (struct wl1271*,struct wl1271_radio_parms_cmd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,struct wl1271_radio_parms_cmd*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_cmd_radio_parms(struct wl1271 *wl)
{
	struct wl1271_nvs_file *nvs = (struct wl1271_nvs_file *)wl->nvs;
	struct wl1271_radio_parms_cmd *radio_parms;
	struct wl1271_ini_general_params *gp = &nvs->general_params;
	int ret, fem_idx;

	if (!wl->nvs)
		return -ENODEV;

	radio_parms = kzalloc(sizeof(*radio_parms), GFP_KERNEL);
	if (!radio_parms)
		return -ENOMEM;

	radio_parms->test.id = TEST_CMD_INI_FILE_RADIO_PARAM;

	fem_idx = WL12XX_FEM_TO_NVS_ENTRY(gp->tx_bip_fem_manufacturer);

	/* 2.4GHz parameters */
	memcpy(&radio_parms->static_params_2, &nvs->stat_radio_params_2,
	       sizeof(struct wl1271_ini_band_params_2));
	memcpy(&radio_parms->dyn_params_2,
	       &nvs->dyn_radio_params_2[fem_idx].params,
	       sizeof(struct wl1271_ini_fem_params_2));

	/* 5GHz parameters */
	memcpy(&radio_parms->static_params_5,
	       &nvs->stat_radio_params_5,
	       sizeof(struct wl1271_ini_band_params_5));
	memcpy(&radio_parms->dyn_params_5,
	       &nvs->dyn_radio_params_5[fem_idx].params,
	       sizeof(struct wl1271_ini_fem_params_5));

	wl1271_dump(DEBUG_CMD, "TEST_CMD_INI_FILE_RADIO_PARAM: ",
		    radio_parms, sizeof(*radio_parms));

	ret = wl1271_cmd_test(wl, radio_parms, sizeof(*radio_parms), 0);
	if (ret < 0)
		wl1271_warning("CMD_INI_FILE_RADIO_PARAM failed");

	kfree(radio_parms);
	return ret;
}