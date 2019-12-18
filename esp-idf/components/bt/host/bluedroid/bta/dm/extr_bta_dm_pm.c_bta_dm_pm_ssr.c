#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ max_lat; int /*<<< orphan*/  min_loc_to; int /*<<< orphan*/  min_rmt_to; } ;
typedef  TYPE_2__ tBTA_DM_SSR_SPEC ;
typedef  size_t UINT8 ;
struct TYPE_11__ {size_t count; TYPE_1__* conn_srvc; } ;
struct TYPE_10__ {size_t app_id; scalar_t__ id; size_t spec_idx; } ;
struct TYPE_9__ {size_t ssr; } ;
struct TYPE_7__ {scalar_t__ id; scalar_t__ app_id; int /*<<< orphan*/  peer_bdaddr; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*,int,scalar_t__) ; 
 scalar_t__ BTA_ALL_APP_ID ; 
 int BTA_DM_PM_SSR0 ; 
 size_t BTA_DM_PM_SSR_HH ; 
 scalar_t__ BTA_HH_ERR ; 
 int /*<<< orphan*/  BTM_SetSsrParams (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_dm_conn_srvcs ; 
 scalar_t__ bta_hh_read_ssr_param (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* p_bta_dm_pm_cfg ; 
 TYPE_4__* p_bta_dm_pm_spec ; 
 TYPE_2__* p_bta_dm_ssr_spec ; 

__attribute__((used)) static void bta_dm_pm_ssr(BD_ADDR peer_addr)
{
    tBTA_DM_SSR_SPEC *p_spec, *p_spec_cur;
    UINT8   i, j;
    int     ssr = BTA_DM_PM_SSR0;

    /* go through the connected services */
    for (i = 0; i < bta_dm_conn_srvcs.count ; i++) {
        if (!bdcmp(bta_dm_conn_srvcs.conn_srvc[i].peer_bdaddr, peer_addr)) {
            /* p_bta_dm_pm_cfg[0].app_id is the number of entries */
            for (j = 1; j <= p_bta_dm_pm_cfg[0].app_id; j++) {
                /* find the associated p_bta_dm_pm_cfg */
                if ((p_bta_dm_pm_cfg[j].id == bta_dm_conn_srvcs.conn_srvc[i].id)
                        && ((p_bta_dm_pm_cfg[j].app_id == BTA_ALL_APP_ID )
                            || (p_bta_dm_pm_cfg[j].app_id == bta_dm_conn_srvcs.conn_srvc[i].app_id))) {
                    APPL_TRACE_WARNING("bta_dm_pm_ssr conn_srvc id:%d, app_id:%d",
                                       bta_dm_conn_srvcs.conn_srvc[i].id, bta_dm_conn_srvcs.conn_srvc[i].app_id);
                    break;
                }
            }

            /* find the ssr index with the smallest max latency. */
            p_spec_cur = &p_bta_dm_ssr_spec[p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr];
            p_spec = &p_bta_dm_ssr_spec[ssr];

#if (defined BTA_HH_INCLUDED && BTA_HH_INCLUDED == TRUE)
            /* HH has the per connection SSR preference, already read the SSR params from BTA HH */
            if (p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr == BTA_DM_PM_SSR_HH) {
                if (bta_hh_read_ssr_param(peer_addr, &p_spec_cur->max_lat, &p_spec_cur->min_rmt_to) == BTA_HH_ERR) {
                    continue;
                }
            }
#endif
            if (p_spec_cur->max_lat < p_spec->max_lat ||
                    (ssr == BTA_DM_PM_SSR0 && p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr != BTA_DM_PM_SSR0)) {
                ssr = p_bta_dm_pm_spec[p_bta_dm_pm_cfg[j].spec_idx].ssr;
            }

        }
    }

    p_spec = &p_bta_dm_ssr_spec[ssr];
    APPL_TRACE_WARNING("bta_dm_pm_ssr:%d, lat:%d", ssr, p_spec->max_lat);
    if (p_spec->max_lat) {
        /* set the SSR parameters. */
        BTM_SetSsrParams (peer_addr, p_spec->max_lat,
                          p_spec->min_rmt_to, p_spec->min_loc_to);
    }
}