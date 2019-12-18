#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ tBT_UUID ;
struct TYPE_15__ {int len; int /*<<< orphan*/ * p_value; } ;
typedef  TYPE_3__ tBTA_GATT_UNFMT ;
struct TYPE_16__ {int /*<<< orphan*/ * characteristics; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_4__ tBTA_GATTC_SERVICE ;
struct TYPE_17__ {int /*<<< orphan*/ * p_srvc_cache; } ;
typedef  TYPE_5__ tBTA_GATTC_SERV ;
typedef  int /*<<< orphan*/  tBTA_GATTC_FIND_SERVICE_CB ;
struct TYPE_18__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_6__ tBTA_GATTC_DESCRIPTOR ;
struct TYPE_19__ {scalar_t__ write_remote_svc_change_ccc_done; int /*<<< orphan*/  svc_change_descr_handle; } ;
typedef  TYPE_7__ tBTA_GATTC_CONN ;
struct TYPE_20__ {int /*<<< orphan*/ * descriptors; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_8__ tBTA_GATTC_CHARACTERISTIC ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_TYPE_WRITE ; 
 int /*<<< orphan*/  BTA_GATTC_WriteCharDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATT_AUTH_REQ_NONE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GATT_CLT_CONFIG_INDICATION ; 
 int /*<<< orphan*/  GATT_UUID_CHAR_CLIENT_CONFIG ; 
 int /*<<< orphan*/  GATT_UUID_GATT_SRV_CHGD ; 
 int /*<<< orphan*/  LEN_UUID_16 ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CACHE_NOT_FOUND ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CCC_NOT_FOUND ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CCC_WRITTEN_SUCCESS ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CHAR_NOT_FOUND ; 
 int /*<<< orphan*/  SERVICE_CHANGE_SERVICE_NOT_FOUND ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UUID_SERVCLASS_GATT_SERVER ; 
 TYPE_7__* bta_gattc_conn_find_alloc (int /*<<< orphan*/ ) ; 
 TYPE_5__* bta_gattc_find_srcb (int /*<<< orphan*/ ) ; 
 scalar_t__ bta_gattc_uuid_compare (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/ *) ; 
 void* list_node (int /*<<< orphan*/ *) ; 

tBTA_GATTC_FIND_SERVICE_CB bta_gattc_register_service_change_notify(UINT16 conn_id, BD_ADDR remote_bda)
{
    tBTA_GATTC_SERV     *p_srcb = NULL;
    list_t              *p_cache = NULL;
    tBTA_GATTC_SERVICE *p_service = NULL;
    tBTA_GATTC_CHARACTERISTIC *p_char = NULL;
    tBTA_GATTC_DESCRIPTOR *p_desc = NULL;
    tBTA_GATTC_FIND_SERVICE_CB    result;
    BOOLEAN             gatt_cache_found = FALSE;
    BOOLEAN             gatt_service_found = FALSE;
    BOOLEAN             gatt_service_change_found = FALSE;
    BOOLEAN             gatt_ccc_found = FALSE;

    tBT_UUID gatt_service_uuid = {LEN_UUID_16, {UUID_SERVCLASS_GATT_SERVER}};
    tBT_UUID gatt_service_change_uuid = {LEN_UUID_16, {GATT_UUID_GATT_SRV_CHGD}};
    tBT_UUID gatt_ccc_uuid = {LEN_UUID_16, {GATT_UUID_CHAR_CLIENT_CONFIG}};
    tBTA_GATTC_CONN *p_conn = bta_gattc_conn_find_alloc(remote_bda);
    if(p_conn && p_conn->write_remote_svc_change_ccc_done) {
        return SERVICE_CHANGE_CCC_WRITTEN_SUCCESS;
    }

    p_srcb = bta_gattc_find_srcb(remote_bda);
    if ((p_srcb != NULL) && (p_srcb->p_srvc_cache != NULL)) {
        p_cache = p_srcb->p_srvc_cache;
        gatt_cache_found = TRUE;
    }
    else {
        result = SERVICE_CHANGE_CACHE_NOT_FOUND;
    }
    /* start to find gatt service */
    if (gatt_cache_found == TRUE) {
        for (list_node_t *sn = list_begin(p_cache);
             sn != list_end(p_cache); sn = list_next(sn)) {
            p_service = list_node(sn);
            if (bta_gattc_uuid_compare(&gatt_service_uuid, &p_service->uuid, TRUE)) {
                gatt_service_found = TRUE;
                break;
            }
        }
    }
    else {
        result = SERVICE_CHANGE_CACHE_NOT_FOUND;
    }

    /* start to find gatt service change characteristic */
    if (gatt_service_found == TRUE) {
        if (p_service->characteristics) {
            for (list_node_t *cn = list_begin(p_service->characteristics);
                 cn != list_end(p_service->characteristics); cn = list_next(cn)) {
                p_char = list_node(cn);
                if (bta_gattc_uuid_compare(&gatt_service_change_uuid, &p_char->uuid, TRUE)) {
                    gatt_service_change_found = TRUE;
                    break;
                }
            }
        }
    }
    else if (gatt_cache_found == TRUE) {
        /* Gatt service not found, start a timer to wait for service discovery */
        result = SERVICE_CHANGE_SERVICE_NOT_FOUND;
    }
    /* start to find gatt service change characteristic ccc */
    if (gatt_service_change_found == TRUE) {
        if (p_char->descriptors) {
            for (list_node_t *dn = list_begin(p_char->descriptors);
                 dn != list_end(p_char->descriptors); dn = list_next(dn)) {
                p_desc = list_node(dn);
                if (bta_gattc_uuid_compare(&gatt_ccc_uuid, &p_desc->uuid, TRUE)) {
                    gatt_ccc_found = TRUE;
                    break;
                }
            }
        }
    }
    else if (gatt_service_found ==TRUE) {
        /* Gatt service found, but service change char not found,
         * Case1: remote device doesn't have service change char, we don't need to start a timer here to
         * wait for service discovery
         * Case2: remote device exist service change char, we have found gatt service, but have not found
         * service change char, we need to start a timer here*/
        result = SERVICE_CHANGE_CHAR_NOT_FOUND;
    }

    if (gatt_ccc_found == TRUE){
        if (p_conn) {
            p_conn->svc_change_descr_handle = p_desc->handle;
            p_conn->write_remote_svc_change_ccc_done = TRUE;
        }
        result = SERVICE_CHANGE_CCC_WRITTEN_SUCCESS;
        uint16_t indicate_value = GATT_CLT_CONFIG_INDICATION;
        tBTA_GATT_UNFMT indicate_v;
        indicate_v.len = 2;
        indicate_v.p_value = (uint8_t *)&indicate_value;
        BTA_GATTC_WriteCharDescr (conn_id, p_desc->handle, BTA_GATTC_TYPE_WRITE, &indicate_v, BTA_GATT_AUTH_REQ_NONE);

    }
    else if (gatt_service_change_found == TRUE) {
        /* Gatt service char found, but service change char ccc not found,
         * Case1: remote device doesn't have service change char ccc, we don't need to start a timer here to
         * wait for service discovery
         * Case2: remote device exist service change char ccc, we have found gatt service change char, but have not found
         * service change char ccc, we need to start a timer here */
        result = SERVICE_CHANGE_CCC_NOT_FOUND;
    }

    return result;
}