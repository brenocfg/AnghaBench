#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* bd_name; int /*<<< orphan*/ * dev_class; int /*<<< orphan*/ * bd_addr; } ;
typedef  TYPE_2__ tBTM_SP_RMT_OOB ;
typedef  int /*<<< orphan*/  tBTM_SP_EVT_DATA ;
struct TYPE_8__ {scalar_t__ sec_bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {scalar_t__ (* p_sp_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  acl_disc_reason; TYPE_1__ api; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,int) ; 
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_MAX_REM_BD_NAME_LEN ; 
 scalar_t__ BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP ; 
 int /*<<< orphan*/  BTM_RemoteOobDataReply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SP_RMT_OOB_EVT ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_SECURITY ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ btm_cb ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_rem_oob_neg_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_rem_oob_req (UINT8 *p)
{
    UINT8 *p_bda;
    tBTM_SP_RMT_OOB  evt_data;
    tBTM_SEC_DEV_REC *p_dev_rec;
    BT_OCTET16      c;
    BT_OCTET16      r;

    p_bda = evt_data.bd_addr;

    STREAM_TO_BDADDR (p_bda, p);

    BTM_TRACE_EVENT ("btm_rem_oob_req() BDA: %02x:%02x:%02x:%02x:%02x:%02x\n",
                     p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    if ( (NULL != (p_dev_rec = btm_find_dev (p_bda))) &&
            btm_cb.api.p_sp_callback) {
        memcpy (evt_data.bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN);
        memcpy (evt_data.dev_class, p_dev_rec->dev_class, DEV_CLASS_LEN);
        BCM_STRNCPY_S((char *)evt_data.bd_name, sizeof(evt_data.bd_name), (char *)p_dev_rec->sec_bd_name, BTM_MAX_REM_BD_NAME_LEN + 1);
        evt_data.bd_name[BTM_MAX_REM_BD_NAME_LEN] = 0;

        btm_sec_change_pairing_state(BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP);
        if ((*btm_cb.api.p_sp_callback) (BTM_SP_RMT_OOB_EVT, (tBTM_SP_EVT_DATA *)&evt_data) == BTM_NOT_AUTHORIZED) {
            BTM_RemoteOobDataReply(TRUE, p_bda, c, r);
        }
        return;
    }

    /* something bad. we can only fail this connection */
    btm_cb.acl_disc_reason = HCI_ERR_HOST_REJECT_SECURITY;
    btsnd_hcic_rem_oob_neg_reply (p_bda);
}