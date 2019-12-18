#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* retrans_window; void* tx_interval; scalar_t__ tx_pkt_len; scalar_t__ rx_pkt_len; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* p_esco_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__ data; } ;
struct TYPE_10__ {scalar_t__ state; scalar_t__ hci_handle; TYPE_3__ esco; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  int /*<<< orphan*/  tBTM_ESCO_EVT_DATA ;
struct TYPE_11__ {void* retrans_window; void* tx_interval; scalar_t__ tx_pkt_len; scalar_t__ rx_pkt_len; scalar_t__ sco_inx; void* hci_status; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_5__ tBTM_CHG_ESCO_EVT_DATA ;
typedef  void* UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {TYPE_4__* sco_db; } ;
struct TYPE_12__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_ESCO_CHG_EVT ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__,void*) ; 
 scalar_t__ SCO_ST_CONNECTED ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_esco_proc_conn_chg (UINT8 status, UINT16 handle, UINT8 tx_interval,
                             UINT8 retrans_window, UINT16 rx_pkt_len,
                             UINT16 tx_pkt_len)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN               *p = &btm_cb.sco_cb.sco_db[0];
    tBTM_CHG_ESCO_EVT_DATA   data;
    UINT16                   xx;

    BTM_TRACE_EVENT("btm_esco_proc_conn_chg -> handle 0x%04x, status 0x%02x",
                    handle, status);

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if (p->state == SCO_ST_CONNECTED && handle == p->hci_handle) {
            /* If upper layer wants notification */
            if (p->esco.p_esco_cback) {
                memcpy(data.bd_addr, p->esco.data.bd_addr, BD_ADDR_LEN);
                data.hci_status = status;
                data.sco_inx = xx;
                data.rx_pkt_len = p->esco.data.rx_pkt_len = rx_pkt_len;
                data.tx_pkt_len = p->esco.data.tx_pkt_len = tx_pkt_len;
                data.tx_interval = p->esco.data.tx_interval = tx_interval;
                data.retrans_window = p->esco.data.retrans_window = retrans_window;

                (*p->esco.p_esco_cback)(BTM_ESCO_CHG_EVT,
                                        (tBTM_ESCO_EVT_DATA *)&data);
            }
            return;
        }
    }
#endif
}