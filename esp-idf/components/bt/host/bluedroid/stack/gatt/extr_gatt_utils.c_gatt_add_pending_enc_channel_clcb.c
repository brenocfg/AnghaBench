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
struct TYPE_6__ {int /*<<< orphan*/  pending_enc_clcb; } ;
typedef  TYPE_1__ tGATT_TCB ;
struct TYPE_7__ {int /*<<< orphan*/ * p_clcb; } ;
typedef  TYPE_2__ tGATT_PENDING_ENC_CLCB ;
typedef  int /*<<< orphan*/  tGATT_CLCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

tGATT_PENDING_ENC_CLCB *gatt_add_pending_enc_channel_clcb(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb )
{
    tGATT_PENDING_ENC_CLCB   *p_buf;

    GATT_TRACE_DEBUG ("gatt_add_pending_new_srv_start");
    if ((p_buf = (tGATT_PENDING_ENC_CLCB *)osi_malloc((UINT16)sizeof(tGATT_PENDING_ENC_CLCB))) != NULL) {
        GATT_TRACE_DEBUG ("enqueue a new pending encryption channel clcb");
        p_buf->p_clcb = p_clcb;
    fixed_queue_enqueue(p_tcb->pending_enc_clcb, p_buf, FIXED_QUEUE_MAX_TIMEOUT);
    }
    return p_buf;
}