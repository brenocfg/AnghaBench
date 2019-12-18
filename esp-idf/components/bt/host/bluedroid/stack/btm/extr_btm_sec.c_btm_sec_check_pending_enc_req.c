#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBT_TRANSPORT ;
struct TYPE_5__ {scalar_t__ psm; scalar_t__ transport; scalar_t__ p_ref_data; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_QUEUE_ENTRY ;
struct TYPE_6__ {int sec_flags; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  sec_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_BLE_SEC_ENCRYPT ; 
 scalar_t__ BTM_BLE_SEC_ENCRYPT_MITM ; 
 scalar_t__ BTM_BLE_SEC_ENCRYPT_NO_MITM ; 
 scalar_t__ BTM_ERR_PROCESSING ; 
 int BTM_SEC_LE_AUTHENTICATED ; 
 scalar_t__ BTM_SUCCESS ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/ * fixed_queue_get_list (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_try_remove_from_queue (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void btm_sec_check_pending_enc_req (tBTM_SEC_DEV_REC  *p_dev_rec, tBT_TRANSPORT transport,
        UINT8 encr_enable)
{
    if (fixed_queue_is_empty(btm_cb.sec_pending_q)) {
        return;
    }

    UINT8 res = encr_enable ? BTM_SUCCESS : BTM_ERR_PROCESSING;
    list_t *list = fixed_queue_get_list(btm_cb.sec_pending_q);
    for (const list_node_t *node = list_begin(list); node != list_end(list); ) {
        tBTM_SEC_QUEUE_ENTRY *p_e = (tBTM_SEC_QUEUE_ENTRY *)list_node(node);
        node = list_next(node);

        if (memcmp(p_e->bd_addr, p_dev_rec->bd_addr, BD_ADDR_LEN) == 0 && p_e->psm == 0
#if BLE_INCLUDED == TRUE
            && p_e->transport == transport
#endif
           ) {
#if BLE_INCLUDED == TRUE
            UINT8 sec_act = *(UINT8 *)(p_e->p_ref_data);
#endif

            if (encr_enable == 0 || transport == BT_TRANSPORT_BR_EDR
#if BLE_INCLUDED == TRUE
                    || (sec_act == BTM_BLE_SEC_ENCRYPT || sec_act == BTM_BLE_SEC_ENCRYPT_NO_MITM)
                    || (sec_act == BTM_BLE_SEC_ENCRYPT_MITM && p_dev_rec->sec_flags
                    & BTM_SEC_LE_AUTHENTICATED)
#endif
               ) {
                if (p_e->p_callback) {
                    (*p_e->p_callback) (p_dev_rec->bd_addr, transport, p_e->p_ref_data, res);
                }

				fixed_queue_try_remove_from_queue(btm_cb.sec_pending_q, (void *)p_e);
            }
        }
    }
}