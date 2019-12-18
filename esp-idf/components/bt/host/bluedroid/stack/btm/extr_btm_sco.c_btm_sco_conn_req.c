#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bd_addr; scalar_t__ link_type; } ;
struct TYPE_10__ {TYPE_2__ data; int /*<<< orphan*/  (* p_esco_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {scalar_t__ state; void* rem_bd_known; TYPE_3__ esco; int /*<<< orphan*/  is_orig; } ;
typedef  TYPE_4__ tSCO_CONN ;
struct TYPE_8__ {int packet_types; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* app_sco_ind_cb ) (scalar_t__) ;TYPE_4__* sco_db; TYPE_1__ def_esco_parms; } ;
typedef  TYPE_5__ tSCO_CB ;
typedef  int /*<<< orphan*/  tBTM_ESCO_EVT_DATA ;
struct TYPE_13__ {scalar_t__ sco_inx; scalar_t__ link_type; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_6__ tBTM_ESCO_CONN_REQ_EVT_DATA ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_14__ {TYPE_5__ sco_cb; } ;
typedef  int /*<<< orphan*/  DEV_CLASS ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_ESCO_CONN_REQ_EVT ; 
 int BTM_ESCO_LINK_ONLY_MASK ; 
 scalar_t__ BTM_LINK_TYPE_ESCO ; 
 scalar_t__ BTM_LINK_TYPE_SCO ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int BTM_SCO_EXCEPTION_PKTS_MASK ; 
 int BTM_SCO_LINK_ONLY_MASK ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_RESOURCES ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 scalar_t__ SCO_ST_CONNECTING ; 
 scalar_t__ SCO_ST_LISTENING ; 
 scalar_t__ SCO_ST_UNUSED ; 
 scalar_t__ SCO_ST_W4_CONN_RSP ; 
 void* TRUE ; 
 TYPE_7__ btm_cb ; 
 int /*<<< orphan*/  btm_esco_conn_rsp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 

void btm_sco_conn_req (BD_ADDR bda,  DEV_CLASS dev_class, UINT8 link_type)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CB     *p_sco = &btm_cb.sco_cb;
    tSCO_CONN   *p = &p_sco->sco_db[0];
    UINT16      xx;
    tBTM_ESCO_CONN_REQ_EVT_DATA evt_data;

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        /*
         * If the sco state is in the SCO_ST_CONNECTING state, we still need
         * to return accept sco to avoid race conditon for sco creation
         */
        int rem_bd_matches = p->rem_bd_known &&
                             !memcmp (p->esco.data.bd_addr, bda, BD_ADDR_LEN);
        if (((p->state == SCO_ST_CONNECTING) && rem_bd_matches) ||
                ((p->state == SCO_ST_LISTENING) && (rem_bd_matches || !p->rem_bd_known))) {
            /* If this guy was a wildcard, he is not one any more */
            p->rem_bd_known = TRUE;
            p->esco.data.link_type = link_type;
            p->state = SCO_ST_W4_CONN_RSP;
            memcpy (p->esco.data.bd_addr, bda, BD_ADDR_LEN);

            /* If no callback, auto-accept the connection if packet types match */
            if (!p->esco.p_esco_cback) {
                /* If requesting eSCO reject if default parameters are SCO only */
                if ((link_type == BTM_LINK_TYPE_ESCO
                        && !(p_sco->def_esco_parms.packet_types & BTM_ESCO_LINK_ONLY_MASK)
                        && ((p_sco->def_esco_parms.packet_types & BTM_SCO_EXCEPTION_PKTS_MASK)
                            == BTM_SCO_EXCEPTION_PKTS_MASK))

                        /* Reject request if SCO is desired but no SCO packets delected */
                        || (link_type == BTM_LINK_TYPE_SCO
                            && !(p_sco->def_esco_parms.packet_types & BTM_SCO_LINK_ONLY_MASK))) {
                    btm_esco_conn_rsp(xx, HCI_ERR_HOST_REJECT_RESOURCES, bda, NULL);
                } else { /* Accept the request */
                    btm_esco_conn_rsp(xx, HCI_SUCCESS, bda, NULL);
                }
            } else { /* Notify upper layer of connect indication */
                memcpy(evt_data.bd_addr, bda, BD_ADDR_LEN);
                memcpy(evt_data.dev_class, dev_class, DEV_CLASS_LEN);
                evt_data.link_type = link_type;
                evt_data.sco_inx = xx;
                p->esco.p_esco_cback(BTM_ESCO_CONN_REQ_EVT, (tBTM_ESCO_EVT_DATA *)&evt_data);
            }

            return;
        }
    }

    /* TCS usage */
    if (btm_cb.sco_cb.app_sco_ind_cb) {
        /* Now, try to find an unused control block */
        for (xx = 0, p = &btm_cb.sco_cb.sco_db[0]; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
            if (p->state == SCO_ST_UNUSED) {
                p->is_orig = FALSE;
                p->state = SCO_ST_LISTENING;

                p->esco.data.link_type = link_type;
                memcpy (p->esco.data.bd_addr, bda, BD_ADDR_LEN);
                p->rem_bd_known = TRUE;
                break;
            }
        }
        if ( xx < BTM_MAX_SCO_LINKS) {
            btm_cb.sco_cb.app_sco_ind_cb(xx);
            return;
        }
    }

#endif
    /* If here, no one wants the SCO connection. Reject it */
    BTM_TRACE_WARNING("btm_sco_conn_req: No one wants this SCO connection; rejecting it");
    btm_esco_conn_rsp(BTM_MAX_SCO_LINKS, HCI_ERR_HOST_REJECT_RESOURCES, bda, NULL);
}