#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  flag; int /*<<< orphan*/  device_type; int /*<<< orphan*/  inq_result_type; int /*<<< orphan*/  ble_addr_type; int /*<<< orphan*/  rssi; int /*<<< orphan*/  dev_class; } ;
typedef  TYPE_2__ tBTM_INQ_RESULTS ;
struct TYPE_11__ {void* appl_knows_rem_name; } ;
typedef  TYPE_3__ tBTM_INQ_INFO ;
struct TYPE_9__ {void* remt_name_not_required; int /*<<< orphan*/ * p_eir; int /*<<< orphan*/  flag; int /*<<< orphan*/  device_type; int /*<<< orphan*/  inq_result_type; int /*<<< orphan*/  ble_addr_type; int /*<<< orphan*/  rssi; void* is_limited; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_12__ {TYPE_1__ inq_res; } ;
typedef  TYPE_4__ tBTA_DM_SEARCH ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_search_cback ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_INQ_RES_EVT ; 
 int /*<<< orphan*/  BTM_COD_SERVICE_CLASS (int,int /*<<< orphan*/ ) ; 
 int BTM_COD_SERVICE_LMTD_DISCOVER ; 
 TYPE_3__* BTM_InqDbRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_dm_search_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void bta_dm_inq_results_cb (tBTM_INQ_RESULTS *p_inq, UINT8 *p_eir)
{

    tBTA_DM_SEARCH     result;
    tBTM_INQ_INFO      *p_inq_info;
    UINT16             service_class;

    bdcpy(result.inq_res.bd_addr, p_inq->remote_bd_addr);
    memcpy(result.inq_res.dev_class, p_inq->dev_class, DEV_CLASS_LEN);
    BTM_COD_SERVICE_CLASS(service_class, p_inq->dev_class);
    result.inq_res.is_limited = (service_class & BTM_COD_SERVICE_LMTD_DISCOVER) ? TRUE : FALSE;
    result.inq_res.rssi = p_inq->rssi;

#if (BLE_INCLUDED == TRUE)
    result.inq_res.ble_addr_type    = p_inq->ble_addr_type;
    result.inq_res.inq_result_type  = p_inq->inq_result_type;
    result.inq_res.device_type      = p_inq->device_type;
    result.inq_res.flag             = p_inq->flag;
#endif

    /* application will parse EIR to find out remote device name */
    result.inq_res.p_eir = p_eir;

    if ((p_inq_info = BTM_InqDbRead(p_inq->remote_bd_addr)) != NULL) {
        /* initialize remt_name_not_required to FALSE so that we get the name by default */
        result.inq_res.remt_name_not_required = FALSE;

    }

    if (bta_dm_search_cb.p_search_cback) {
        bta_dm_search_cb.p_search_cback(BTA_DM_INQ_RES_EVT, &result);
    }

    if (p_inq_info) {
        /* application indicates if it knows the remote name, inside the callback
         copy that to the inquiry data base*/
        if (result.inq_res.remt_name_not_required) {
            p_inq_info->appl_knows_rem_name = TRUE;
        }

    }


}