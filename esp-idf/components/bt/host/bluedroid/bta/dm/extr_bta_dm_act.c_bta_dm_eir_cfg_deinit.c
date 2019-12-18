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
struct TYPE_2__ {int /*<<< orphan*/ * bta_dm_eir_url; scalar_t__ bta_dm_eir_url_len; int /*<<< orphan*/ * bta_dm_eir_manufac_spec; scalar_t__ bta_dm_eir_manufac_spec_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* p_bta_dm_eir_cfg ; 

__attribute__((used)) static void bta_dm_eir_cfg_deinit(void)
{
    p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec_len = 0;
    if (p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec) {
        osi_free(p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec);
        p_bta_dm_eir_cfg->bta_dm_eir_manufac_spec = NULL;
    }

    p_bta_dm_eir_cfg->bta_dm_eir_url_len = 0;
    if (p_bta_dm_eir_cfg->bta_dm_eir_url) {
        osi_free(p_bta_dm_eir_cfg->bta_dm_eir_url);
        p_bta_dm_eir_cfg->bta_dm_eir_url = NULL;
    }
}