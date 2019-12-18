#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pending_enc_clcb; } ;
typedef  TYPE_3__ tGATT_TCB ;
struct TYPE_13__ {int /*<<< orphan*/  p_clcb; } ;
typedef  TYPE_4__ tGATT_PENDING_ENC_CLCB ;
typedef  size_t UINT8 ;
struct TYPE_14__ {TYPE_2__* cl_rcb; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_enc_cmpl_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  gatt_if; TYPE_1__ app_cb; scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 size_t GATT_MAX_APPS ; 
 scalar_t__ GATT_SEC_ENC_PENDING ; 
 int /*<<< orphan*/  GATT_SEC_NONE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t fixed_queue_length (int /*<<< orphan*/ ) ; 
 TYPE_9__ gatt_cb ; 
 TYPE_3__* gatt_find_tcb_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_get_sec_act (TYPE_3__*) ; 
 int /*<<< orphan*/  gatt_security_check_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_set_sec_act (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gatt_notify_enc_cmpl(BD_ADDR bd_addr)
{
    tGATT_TCB   *p_tcb;
    UINT8        i = 0;

    if ((p_tcb = gatt_find_tcb_by_addr(bd_addr, BT_TRANSPORT_LE)) != NULL) {
        for (i = 0; i < GATT_MAX_APPS; i++) {
            if (gatt_cb.cl_rcb[i].in_use && gatt_cb.cl_rcb[i].app_cb.p_enc_cmpl_cb) {
                (*gatt_cb.cl_rcb[i].app_cb.p_enc_cmpl_cb)(gatt_cb.cl_rcb[i].gatt_if, bd_addr);
            }
        }

        if (gatt_get_sec_act(p_tcb) == GATT_SEC_ENC_PENDING) {
            gatt_set_sec_act(p_tcb, GATT_SEC_NONE);

            size_t count = fixed_queue_length(p_tcb->pending_enc_clcb);
            for (; count > 0; count--) {
                tGATT_PENDING_ENC_CLCB *p_buf =
                    (tGATT_PENDING_ENC_CLCB *)fixed_queue_dequeue(p_tcb->pending_enc_clcb, 0);
                if (p_buf != NULL) {
                    gatt_security_check_start(p_buf->p_clcb);
                    osi_free(p_buf);
                } else {
                    break;
                }
            }
        }
    } else {
        GATT_TRACE_DEBUG("notify GATT for encryption completion of unknown device");
    }
    return;
}