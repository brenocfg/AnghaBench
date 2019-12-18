#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; int /*<<< orphan*/  at_cb; int /*<<< orphan*/  conn_handle; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int BTA_AG_RFC_READ_MAX ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 scalar_t__ PORT_ReadData (int /*<<< orphan*/ ,char*,int,scalar_t__*) ; 
 scalar_t__ PORT_SUCCESS ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_at_parse (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  bta_sys_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void bta_ag_rfc_data(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UINT16  len;
    char    buf[BTA_AG_RFC_READ_MAX];
    UNUSED(p_data);
    memset(buf, 0, BTA_AG_RFC_READ_MAX);

    APPL_TRACE_DEBUG("bta_ag_rfc_data");
    /* do the following */
    for (;;) {
        /* read data from rfcomm; if bad status, we're done */
        if (PORT_ReadData(p_scb->conn_handle, buf, BTA_AG_RFC_READ_MAX, &len) != PORT_SUCCESS) {
            break;
        }
        /* if no data, we're done */
        if (len == 0) {
            break;
        }
        /* run AT command interpreter on data */
        bta_sys_busy(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
        bta_ag_at_parse(&p_scb->at_cb, buf, len);
        bta_sys_idle(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
        /* no more data to read, we're done */
        if (len < BTA_AG_RFC_READ_MAX) {
            break;
        }
    }
}