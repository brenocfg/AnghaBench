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
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_RFC ;
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_7__ {scalar_t__ p_disc_db; scalar_t__ conn_handle; } ;
struct TYPE_9__ {TYPE_2__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_RFC_CLOSE_EVT ; 
 int /*<<< orphan*/  RFCOMM_RemoveConnection (scalar_t__) ; 
 int /*<<< orphan*/  SDP_CancelServiceSearch (scalar_t__) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_free_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

void bta_hf_client_rfc_do_close(tBTA_HF_CLIENT_DATA *p_data)
{
    tBTA_HF_CLIENT_RFC     *p_buf;
    UNUSED(p_data);

    if (bta_hf_client_cb.scb.conn_handle) {
        RFCOMM_RemoveConnection(bta_hf_client_cb.scb.conn_handle);
    } else {
        /* Close API was called while HF Client is in Opening state.        */
        /* Need to trigger the state machine to send callback to the app    */
        /* and move back to INIT state.                                     */
        if ((p_buf = (tBTA_HF_CLIENT_RFC *) osi_malloc(sizeof(tBTA_HF_CLIENT_RFC))) != NULL) {
            p_buf->hdr.event = BTA_HF_CLIENT_RFC_CLOSE_EVT;
            bta_sys_sendmsg(p_buf);
        }

        /* Cancel SDP if it had been started. */
        if (bta_hf_client_cb.scb.p_disc_db) {
            (void)SDP_CancelServiceSearch (bta_hf_client_cb.scb.p_disc_db);
            bta_hf_client_free_db(NULL);
        }
    }
}