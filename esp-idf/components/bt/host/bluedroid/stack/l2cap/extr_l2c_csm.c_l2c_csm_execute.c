#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int chnl_state; } ;
typedef  TYPE_1__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
#define  CST_CLOSED 136 
#define  CST_CONFIG 135 
#define  CST_OPEN 134 
#define  CST_ORIG_W4_SEC_COMP 133 
#define  CST_TERM_W4_SEC_COMP 132 
#define  CST_W4_L2CAP_CONNECT_RSP 131 
#define  CST_W4_L2CAP_DISCONNECT_RSP 130 
#define  CST_W4_L2CA_CONNECT_RSP 129 
#define  CST_W4_L2CA_DISCONNECT_RSP 128 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_closed (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_config (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_open (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_orig_w4_sec_comp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_term_w4_sec_comp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_w4_l2ca_connect_rsp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_w4_l2ca_disconnect_rsp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_w4_l2cap_connect_rsp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l2c_csm_w4_l2cap_disconnect_rsp (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

void l2c_csm_execute (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    switch (p_ccb->chnl_state) {
    case CST_CLOSED:
        l2c_csm_closed (p_ccb, event, p_data);
        break;

    case CST_ORIG_W4_SEC_COMP:
        l2c_csm_orig_w4_sec_comp (p_ccb, event, p_data);
        break;

    case CST_TERM_W4_SEC_COMP:
        l2c_csm_term_w4_sec_comp (p_ccb, event, p_data);
        break;

    case CST_W4_L2CAP_CONNECT_RSP:
        l2c_csm_w4_l2cap_connect_rsp (p_ccb, event, p_data);
        break;

    case CST_W4_L2CA_CONNECT_RSP:
        l2c_csm_w4_l2ca_connect_rsp (p_ccb, event, p_data);
        break;

    case CST_CONFIG:
        l2c_csm_config (p_ccb, event, p_data);
        break;

    case CST_OPEN:
        l2c_csm_open (p_ccb, event, p_data);
        break;

    case CST_W4_L2CAP_DISCONNECT_RSP:
        l2c_csm_w4_l2cap_disconnect_rsp (p_ccb, event, p_data);
        break;

    case CST_W4_L2CA_DISCONNECT_RSP:
        l2c_csm_w4_l2ca_disconnect_rsp (p_ccb, event, p_data);
        break;

    default:
        L2CAP_TRACE_DEBUG("Unhandled event! event = %d", event);
        break;
    }
}