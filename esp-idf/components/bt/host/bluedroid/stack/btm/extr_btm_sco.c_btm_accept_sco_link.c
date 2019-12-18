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
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  link_type; } ;
struct TYPE_10__ {TYPE_1__ data; } ;
struct TYPE_12__ {TYPE_2__ esco; int /*<<< orphan*/ * p_disc_cb; int /*<<< orphan*/ * p_conn_cb; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  int /*<<< orphan*/  tBTM_SCO_CB ;
struct TYPE_13__ {int /*<<< orphan*/  packet_types; } ;
typedef  TYPE_5__ tBTM_ESCO_PARAMS ;
typedef  size_t UINT16 ;
struct TYPE_11__ {TYPE_4__* sco_db; } ;
struct TYPE_14__ {TYPE_3__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_LINK_TYPE_ESCO ; 
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,size_t) ; 
 int /*<<< orphan*/  HCI_SUCCESS ; 
 TYPE_7__ btm_cb ; 
 int /*<<< orphan*/  btm_esco_conn_rsp (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  btm_reject_sco_link (size_t) ; 

void btm_accept_sco_link(UINT16 sco_inx, tBTM_ESCO_PARAMS *p_setup,
                         tBTM_SCO_CB *p_conn_cb, tBTM_SCO_CB *p_disc_cb)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN        *p_sco;

    if (sco_inx >= BTM_MAX_SCO_LINKS) {
        BTM_TRACE_ERROR("btm_accept_sco_link: Invalid sco_inx(%d)", sco_inx);
        return;
    }

    /* Link role is ignored in for this message */
    p_sco = &btm_cb.sco_cb.sco_db[sco_inx];
    p_sco->p_conn_cb = p_conn_cb;
    p_sco->p_disc_cb = p_disc_cb;
    p_sco->esco.data.link_type = BTM_LINK_TYPE_ESCO; /* Accept with all supported types */

    BTM_TRACE_DEBUG("TCS accept SCO: Packet Types 0x%04x", p_setup->packet_types);

    btm_esco_conn_rsp(sco_inx, HCI_SUCCESS, p_sco->esco.data.bd_addr, p_setup);
#else
    btm_reject_sco_link(sco_inx);
#endif
}