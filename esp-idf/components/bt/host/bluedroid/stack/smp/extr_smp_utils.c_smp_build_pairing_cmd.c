#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  local_r_key; int /*<<< orphan*/  local_i_key; int /*<<< orphan*/  loc_enc_size; int /*<<< orphan*/  loc_auth_req; int /*<<< orphan*/  loc_oob_flag; int /*<<< orphan*/  local_io_capability; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int offset; int len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int L2CAP_MIN_OFFSET ; 
 int SMP_PAIRING_REQ_SIZE ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

BT_HDR *smp_build_pairing_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;

    SMP_TRACE_EVENT("smp_build_pairing_cmd");
    if ((p_buf = (BT_HDR *)osi_malloc(sizeof(BT_HDR) + SMP_PAIRING_REQ_SIZE + L2CAP_MIN_OFFSET)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, cmd_code);
        UINT8_TO_STREAM (p, p_cb->local_io_capability);
        UINT8_TO_STREAM (p, p_cb->loc_oob_flag);
        UINT8_TO_STREAM (p, p_cb->loc_auth_req);
        UINT8_TO_STREAM (p, p_cb->loc_enc_size);
        UINT8_TO_STREAM (p, p_cb->local_i_key);
        UINT8_TO_STREAM (p, p_cb->local_r_key);

        p_buf->offset = L2CAP_MIN_OFFSET;
        /* 1B ERR_RSP op code + 1B cmd_op_code + 2B handle + 1B status */
        p_buf->len = SMP_PAIRING_REQ_SIZE;
    }

    return p_buf;
}