#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  port_handle; } ;
struct TYPE_9__ {TYPE_2__ rfc; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_DATA ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  conn_handle; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  colli_timer; scalar_t__ colli_tmr_on; int /*<<< orphan*/  serv_handle; int /*<<< orphan*/  role; } ;
struct TYPE_10__ {TYPE_1__ scb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_ACP ; 
 scalar_t__ FALSE ; 
 int PORT_CheckConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PORT_SUCCESS ; 
 scalar_t__ bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_do_disc () ; 
 int /*<<< orphan*/  bta_hf_client_resume_open () ; 
 int /*<<< orphan*/  bta_hf_client_rfc_open (TYPE_3__*) ; 
 int /*<<< orphan*/  bta_sys_free_timer (int /*<<< orphan*/ *) ; 

void bta_hf_client_rfc_acp_open(tBTA_HF_CLIENT_DATA *p_data)
{
    UINT16          lcid;
    BD_ADDR         dev_addr;
    int             status;

    /* set role */
    bta_hf_client_cb.scb.role = BTA_HF_CLIENT_ACP;

    APPL_TRACE_DEBUG ("bta_hf_client_rfc_acp_open: serv_handle = %d rfc.port_handle = %d",
                      bta_hf_client_cb.scb.serv_handle, p_data->rfc.port_handle);

    /* get bd addr of peer */
    if (PORT_SUCCESS != (status = PORT_CheckConnection(p_data->rfc.port_handle, dev_addr, &lcid))) {
        APPL_TRACE_DEBUG ("bta_hf_client_rfc_acp_open error PORT_CheckConnection returned status %d", status);
    }

    /* Collision Handling */
    if (bta_hf_client_cb.scb.colli_tmr_on) {
        /* stop collision timer */
        bta_hf_client_cb.scb.colli_tmr_on = FALSE;
        bta_sys_free_timer (&bta_hf_client_cb.scb.colli_timer);

        if (bdcmp (dev_addr, bta_hf_client_cb.scb.peer_addr) == 0) {
            /* If incoming and outgoing device are same, nothing more to do.            */
            /* Outgoing conn will be aborted because we have successful incoming conn.  */
        } else {
            /* Resume outgoing connection. */
            bta_hf_client_resume_open ();
        }
    }

    bdcpy (bta_hf_client_cb.scb.peer_addr, dev_addr);
    bta_hf_client_cb.scb.conn_handle = p_data->rfc.port_handle;

    /* do service discovery to get features */
    bta_hf_client_do_disc();

    /* continue with open processing */
    bta_hf_client_rfc_open(p_data);
}