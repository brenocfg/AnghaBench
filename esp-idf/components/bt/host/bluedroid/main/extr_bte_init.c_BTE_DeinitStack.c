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

/* Variables and functions */
 int /*<<< orphan*/  A2D_Deinit () ; 
 int /*<<< orphan*/  AVRC_Deinit () ; 
 int /*<<< orphan*/  GAP_Deinit () ; 
 int /*<<< orphan*/  RFCOMM_Deinit () ; 
 int /*<<< orphan*/ * avct_cb_ptr ; 
 int /*<<< orphan*/ * avdt_cb_ptr ; 
 int /*<<< orphan*/ * bta_ar_cb_ptr ; 
 int /*<<< orphan*/ * bta_av_cb_ptr ; 
 int /*<<< orphan*/ * bta_av_sbc_ups_cb_ptr ; 
 int /*<<< orphan*/ * bta_dm_cb_ptr ; 
 int /*<<< orphan*/ * bta_dm_conn_srvcs_ptr ; 
 int /*<<< orphan*/ * bta_dm_di_cb_ptr ; 
 int /*<<< orphan*/ * bta_dm_search_cb_ptr ; 
 int /*<<< orphan*/ * bta_gattc_cb_ptr ; 
 int /*<<< orphan*/ * bta_gatts_cb_ptr ; 
 int /*<<< orphan*/ * bta_hf_client_cb_ptr ; 
 int /*<<< orphan*/ * bta_hh_cb_ptr ; 
 int /*<<< orphan*/ * bta_jv_cb_ptr ; 
 int /*<<< orphan*/ * bta_sdp_cb_ptr ; 
 int /*<<< orphan*/ * bta_sys_cb_ptr ; 
 int /*<<< orphan*/ * g_disc_raw_data_buf ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void BTE_DeinitStack(void)
{
    //BTA Modules
#if (BTA_INCLUDED == TRUE && BTA_DYNAMIC_MEMORY == TRUE)
#if GATTS_INCLUDED == TRUE
    if (bta_gatts_cb_ptr){
        osi_free(bta_gatts_cb_ptr);
        bta_gatts_cb_ptr = NULL;
    }
#endif
#if GATTC_INCLUDED==TRUE
    if (bta_gattc_cb_ptr){
        osi_free(bta_gattc_cb_ptr);
        bta_gattc_cb_ptr = NULL;
    }
#endif
#if BTA_HH_INCLUDED==TRUE
    if (bta_hh_cb_ptr){
        osi_free(bta_hh_cb_ptr);
        bta_hh_cb_ptr = NULL;
    }
#endif
#if BTA_AV_INCLUDED==TRUE
    if (bta_av_cb_ptr){
        osi_free(bta_av_cb_ptr);
        bta_av_cb_ptr = NULL;
    }
    if (bta_av_sbc_ups_cb_ptr){
        osi_free(bta_av_sbc_ups_cb_ptr);
        bta_av_sbc_ups_cb_ptr = NULL;
    }
#endif
#if BTA_AR_INCLUDED==TRUE
    if (bta_ar_cb_ptr){
        osi_free(bta_ar_cb_ptr);
        bta_ar_cb_ptr = NULL;
    }
#endif
#if SDP_INCLUDED == TRUE
    if (g_disc_raw_data_buf){
        osi_free(g_disc_raw_data_buf);
        g_disc_raw_data_buf = NULL;
    }
#endif
#if BTA_SDP_INCLUDED == TRUE
    if (bta_sdp_cb_ptr){
        osi_free(bta_sdp_cb_ptr);
        bta_sdp_cb_ptr = NULL;
    }
#endif
#if (defined BTA_JV_INCLUDED && BTA_JV_INCLUDED == TRUE)
    if (bta_jv_cb_ptr){
        osi_free(bta_jv_cb_ptr);
        bta_jv_cb_ptr = NULL;
    }
#endif //JV
#if (defined BTA_HF_INCLUDED && BTA_HF_INCLUDED == TRUE)
    if (bta_hf_client_cb_ptr){
        osi_free(bta_hf_client_cb_ptr);
        bta_hf_client_cb_ptr = NULL;
    }
#endif
    if (bta_dm_conn_srvcs_ptr){
        osi_free(bta_dm_conn_srvcs_ptr);
        bta_dm_conn_srvcs_ptr = NULL;
    }
    if (bta_dm_di_cb_ptr){
        osi_free(bta_dm_di_cb_ptr);
        bta_dm_di_cb_ptr = NULL;
    }
    if (bta_dm_search_cb_ptr){
        osi_free(bta_dm_search_cb_ptr);
        bta_dm_search_cb_ptr = NULL;
    }
    if (bta_dm_cb_ptr){
        osi_free(bta_dm_cb_ptr);
        bta_dm_cb_ptr = NULL;
    }
    if (bta_sys_cb_ptr){
        osi_free(bta_sys_cb_ptr);
        bta_sys_cb_ptr = NULL;
    }
#endif // BTA_INCLUDED == TRUE

#if (defined(GAP_INCLUDED) && GAP_INCLUDED == TRUE)
    GAP_Deinit();
#endif

#if (defined(AVCT_INCLUDED) && AVCT_INCLUDED == TRUE && AVCT_DYNAMIC_MEMORY == TRUE)
    if (avct_cb_ptr){
        osi_free(avct_cb_ptr);
        avct_cb_ptr = NULL;
    }
#endif

#if (defined(AVDT_INCLUDED) && AVDT_INCLUDED == TRUE && AVDT_DYNAMIC_MEMORY == TRUE)
    if (avdt_cb_ptr){
        osi_free(avdt_cb_ptr);
        avdt_cb_ptr = NULL;
    }
#endif

#if (defined(AVRC_INCLUDED) && AVRC_INCLUDED == TRUE)
    AVRC_Deinit();
#endif

#if (defined(A2D_INCLUDED) && A2D_INCLUDED == TRUE)
    A2D_Deinit();
#endif

#if (defined(RFCOMM_INCLUDED) && RFCOMM_INCLUDED == TRUE)
    RFCOMM_Deinit();
#endif
}