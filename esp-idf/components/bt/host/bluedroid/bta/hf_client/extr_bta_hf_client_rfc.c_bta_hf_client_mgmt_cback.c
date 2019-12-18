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
struct TYPE_7__ {scalar_t__ event; } ;
struct TYPE_8__ {scalar_t__ port_handle; TYPE_2__ hdr; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_RFC ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ conn_handle; scalar_t__ serv_handle; } ;
struct TYPE_9__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,scalar_t__) ; 
 scalar_t__ BTA_HF_CLIENT_RFC_CLOSE_EVT ; 
 scalar_t__ BTA_HF_CLIENT_RFC_OPEN_EVT ; 
 scalar_t__ BTA_HF_CLIENT_RFC_SRV_CLOSE_EVT ; 
 scalar_t__ PORT_SUCCESS ; 
 TYPE_5__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_hf_client_mgmt_cback(UINT32 code, UINT16 port_handle)
{
    tBTA_HF_CLIENT_RFC     *p_buf;
    UINT16                  event;

    APPL_TRACE_DEBUG("bta_hf_client_mgmt_cback : code = %d, port_handle = %d, conn_handle = %d, serv_handle = %d",
                     code, port_handle, bta_hf_client_cb.scb.conn_handle, bta_hf_client_cb.scb.serv_handle);

    /* ignore close event for port handles other than connected handle */
    if ((code != PORT_SUCCESS) && (port_handle != bta_hf_client_cb.scb.conn_handle)) {
        APPL_TRACE_DEBUG("bta_hf_client_mgmt_cback ignoring handle:%d", port_handle);
        return;
    }

    if (code == PORT_SUCCESS) {
        if ((bta_hf_client_cb.scb.conn_handle && (port_handle == bta_hf_client_cb.scb.conn_handle)) || /* outgoing connection */
                (port_handle == bta_hf_client_cb.scb.serv_handle)) {                     /* incoming connection */
            event = BTA_HF_CLIENT_RFC_OPEN_EVT;
        } else {
            APPL_TRACE_ERROR ("bta_hf_client_mgmt_cback: PORT_SUCCESS, ignoring handle = %d", port_handle);
            return;
        }
    }
    /* distinguish server close events */
    else if (port_handle == bta_hf_client_cb.scb.conn_handle) {
        event = BTA_HF_CLIENT_RFC_CLOSE_EVT;
    } else {
        event = BTA_HF_CLIENT_RFC_SRV_CLOSE_EVT;
    }

    if ((p_buf = (tBTA_HF_CLIENT_RFC *) osi_malloc(sizeof(tBTA_HF_CLIENT_RFC))) != NULL) {
        p_buf->hdr.event = event;
        p_buf->port_handle = port_handle;
        bta_sys_sendmsg(p_buf);
    }
}