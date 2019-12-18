#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * p_esco_cback; } ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ hci_handle; scalar_t__ sent_not_acked; int /*<<< orphan*/  (* p_disc_cb ) (scalar_t__) ;TYPE_2__ esco; int /*<<< orphan*/  rem_bd_known; } ;
typedef  TYPE_3__ tSCO_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {scalar_t__ xmit_window_size; scalar_t__ num_lm_sco_bufs; TYPE_3__* sco_db; int /*<<< orphan*/  sco_disc_reason; } ;
struct TYPE_8__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_INVALID_HCI_HANDLE ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCO_ST_LISTENING ; 
 scalar_t__ SCO_ST_UNUSED ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_sco_flush_sco_data (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void btm_sco_removed (UINT16 hci_handle, UINT8 reason)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[0];
    UINT16      xx;
#endif

    btm_cb.sco_cb.sco_disc_reason = reason;

#if (BTM_MAX_SCO_LINKS>0)
    p = &btm_cb.sco_cb.sco_db[0];
    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if ((p->state != SCO_ST_UNUSED) && (p->state != SCO_ST_LISTENING) && (p->hci_handle == hci_handle)) {
            btm_sco_flush_sco_data(xx);

            p->state = SCO_ST_UNUSED;
#if BTM_SCO_HCI_INCLUDED == TRUE
            btm_cb.sco_cb.xmit_window_size += p->sent_not_acked;
            /* avoid overflow */
            if (btm_cb.sco_cb.xmit_window_size > btm_cb.sco_cb.num_lm_sco_bufs) {
                btm_cb.sco_cb.xmit_window_size = btm_cb.sco_cb.num_lm_sco_bufs;
            }
            p->sent_not_acked = 0;
#endif
            p->hci_handle = BTM_INVALID_HCI_HANDLE;
            p->rem_bd_known = FALSE;
            p->esco.p_esco_cback = NULL;    /* Deregister eSCO callback */
            (*p->p_disc_cb)(xx);

            return;
        }
    }
#endif
}