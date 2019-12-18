#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pending_enc_clcb; int /*<<< orphan*/  sec_act; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_7__ {int /*<<< orphan*/  p_clcb; } ;
typedef  TYPE_2__ tGATT_PENDING_ENC_CLCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  scalar_t__ tBTM_STATUS ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_GetSecurityFlagsByTransport (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int BTM_SEC_FLAG_LKEY_AUTHED ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GATT_SEC_ENCRYPT_MITM ; 
 scalar_t__ GATT_SEC_ENC_PENDING ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t fixed_queue_length (int /*<<< orphan*/ ) ; 
 TYPE_1__* gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_get_sec_act (TYPE_1__*) ; 
 int /*<<< orphan*/  gatt_sec_check_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_security_check_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 

void gatt_enc_cmpl_cback(BD_ADDR bd_addr, tBT_TRANSPORT transport, void *p_ref_data, tBTM_STATUS result)
{
    tGATT_TCB   *p_tcb;
    UINT8       sec_flag;
    BOOLEAN     status = FALSE;
    UNUSED(p_ref_data);

    GATT_TRACE_DEBUG("gatt_enc_cmpl_cback");
    if ((p_tcb = gatt_find_tcb_by_addr(bd_addr, transport)) != NULL) {
        if (gatt_get_sec_act(p_tcb) == GATT_SEC_ENC_PENDING) {
            return;
        }
        tGATT_PENDING_ENC_CLCB *p_buf =
            (tGATT_PENDING_ENC_CLCB *)fixed_queue_dequeue(p_tcb->pending_enc_clcb, 0);
        if (p_buf != NULL) {
            if (result == BTM_SUCCESS) {
                if (gatt_get_sec_act(p_tcb) == GATT_SEC_ENCRYPT_MITM ) {
                    BTM_GetSecurityFlagsByTransport(bd_addr, &sec_flag, transport);

                    if (sec_flag & BTM_SEC_FLAG_LKEY_AUTHED) {
                        status = TRUE;
                    }
                } else {
                    status = TRUE;
                }
            }
            gatt_sec_check_complete(status , p_buf->p_clcb, p_tcb->sec_act);
            osi_free(p_buf);
            /* start all other pending operation in queue */
            for (size_t count = fixed_queue_length(p_tcb->pending_enc_clcb);
                 count > 0; count--) {
                p_buf = (tGATT_PENDING_ENC_CLCB *)fixed_queue_dequeue(p_tcb->pending_enc_clcb, 0);
                if (p_buf != NULL) {
                    gatt_security_check_start(p_buf->p_clcb);
                    osi_free(p_buf);
                } else {
                    break;
                }
            }
        } else {
            GATT_TRACE_ERROR("Unknown operation encryption completed");
        }
    } else {
        GATT_TRACE_ERROR("enc callback for unknown bd_addr");
    }
}