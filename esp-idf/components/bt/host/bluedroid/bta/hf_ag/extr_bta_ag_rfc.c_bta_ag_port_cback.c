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
struct TYPE_5__ {scalar_t__ conn_handle; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ layer_specific; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTA_AG_RFC_DATA_EVT ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_1__* bta_ag_scb_by_idx (scalar_t__) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_ag_port_cback(UINT32 code, UINT16 port_handle, UINT16 handle)
{
    BT_HDR      *p_buf;
    tBTA_AG_SCB *p_scb;
    UNUSED(code);

    if ((p_scb = bta_ag_scb_by_idx(handle)) != NULL) {
        /* ignore port events for port handles other than connected handle */
        if (port_handle != p_scb->conn_handle) {
            APPL_TRACE_DEBUG("ag_port_cback ignoring handle:%d conn_handle = %d other handle = %d",
                              port_handle, p_scb->conn_handle, handle);
            return;
        }

        if ((p_buf = (BT_HDR *) osi_malloc(sizeof(BT_HDR))) != NULL) {
            p_buf->event = BTA_AG_RFC_DATA_EVT;
            p_buf->layer_specific = handle;
            bta_sys_sendmsg(p_buf);
        }
    }
}