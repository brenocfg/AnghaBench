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
struct TYPE_2__ {int bta_dm_eir_min_name_len; int bta_dm_eir_inq_tx_power; int /*<<< orphan*/ * bta_dm_eir_url; scalar_t__ bta_dm_eir_url_len; int /*<<< orphan*/ * bta_dm_eir_manufac_spec; scalar_t__ bta_dm_eir_manufac_spec_len; scalar_t__ bta_dm_eir_flags; int /*<<< orphan*/  bta_dm_eir_included_tx_power; int /*<<< orphan*/  bta_dm_eir_included_uuid; int /*<<< orphan*/  bta_dm_eir_fec_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_EIR_DEFAULT_FEC_REQUIRED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* p_bta_dm_eir_cfg ; 

__attribute__((used)) static void bta_dm_eir_cfg_init(void)
{
    p_bta_dm_eir_cfg->bta_dm_eir_fec_required = BTM_EIR_DEFAULT_FEC_REQUIRED;
    p_bta_dm_eir_cfg->bta_dm_eir_min_name_len = 50;

    p_bta_dm_eir_cfg->bta_dm_eir_included_uuid = TRUE;
    p_bta_dm_eir_cfg->bta_dm_eir_included_tx_power = FALSE;
    p_bta_dm_eir_cfg->bta_dm_eir_inq_tx_power = 3;
    p_bta_dm_eir_cfg->bta_dm_eir_flags = 0;

    p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec_len = 0;
    p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec = NULL;

    p_bta_dm_eir_cfg->bta_dm_eir_url_len = 0;
    p_bta_dm_eir_cfg->bta_dm_eir_url = NULL;
}