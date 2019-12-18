#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bta_dm_eir_url; int /*<<< orphan*/  bta_dm_eir_url_len; int /*<<< orphan*/  bta_dm_eir_manufac_spec; int /*<<< orphan*/  bta_dm_eir_manufac_spec_len; int /*<<< orphan*/  bta_dm_eir_flags; int /*<<< orphan*/  bta_dm_eir_included_uuid; int /*<<< orphan*/  bta_dm_eir_included_tx_power; int /*<<< orphan*/  bta_dm_eir_fec_required; } ;
typedef  TYPE_2__ tBTA_DM_EIR_CONF ;
struct TYPE_9__ {int /*<<< orphan*/  p_url; int /*<<< orphan*/  url_len; int /*<<< orphan*/  p_manufacturer_data; int /*<<< orphan*/  manufacturer_len; int /*<<< orphan*/  flag; int /*<<< orphan*/  include_uuid; int /*<<< orphan*/  include_txpower; int /*<<< orphan*/  fec_required; } ;
typedef  TYPE_3__ esp_bt_eir_data_t ;
struct TYPE_7__ {TYPE_3__ eir_data; } ;
struct TYPE_10__ {TYPE_1__ config_eir; } ;
typedef  TYPE_4__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmConfigEir (TYPE_2__*) ; 

__attribute__((used)) static void btc_gap_bt_config_eir(btc_gap_bt_args_t *arg)
{
    tBTA_DM_EIR_CONF eir_config;
    esp_bt_eir_data_t *eir_data = &arg->config_eir.eir_data;

    eir_config.bta_dm_eir_fec_required = eir_data->fec_required;
    eir_config.bta_dm_eir_included_tx_power = eir_data->include_txpower;
    eir_config.bta_dm_eir_included_uuid = eir_data->include_uuid;
    eir_config.bta_dm_eir_flags = eir_data->flag;
    eir_config.bta_dm_eir_manufac_spec_len = eir_data->manufacturer_len;
    eir_config.bta_dm_eir_manufac_spec = eir_data->p_manufacturer_data;
    eir_config.bta_dm_eir_url_len = eir_data->url_len;
    eir_config.bta_dm_eir_url = eir_data->p_url;

    BTA_DmConfigEir(&eir_config);
}