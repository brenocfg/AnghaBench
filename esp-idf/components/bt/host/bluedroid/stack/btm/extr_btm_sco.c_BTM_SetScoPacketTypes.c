#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  retrans_effort; int /*<<< orphan*/  max_latency; } ;
struct TYPE_9__ {TYPE_3__ setup; } ;
struct TYPE_11__ {TYPE_2__ esco; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_12__ {size_t packet_types; int /*<<< orphan*/  retrans_effort; int /*<<< orphan*/  max_latency; } ;
typedef  TYPE_5__ tBTM_CHG_ESCO_PARAMS ;
typedef  size_t UINT16 ;
struct TYPE_8__ {TYPE_4__* sco_db; } ;
struct TYPE_13__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ChangeEScoLinkParms (size_t,TYPE_5__*) ; 
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 TYPE_6__ btm_cb ; 

tBTM_STATUS BTM_SetScoPacketTypes (UINT16 sco_inx, UINT16 pkt_types)
{
#if (BTM_MAX_SCO_LINKS>0)
    tBTM_CHG_ESCO_PARAMS parms;
    tSCO_CONN           *p;

    /* Validity check */
    if (sco_inx >= BTM_MAX_SCO_LINKS) {
        return (BTM_UNKNOWN_ADDR);
    }

    p = &btm_cb.sco_cb.sco_db[sco_inx];
    parms.packet_types = pkt_types;

    /* Keep the other parameters the same for SCO */
    parms.max_latency = p->esco.setup.max_latency;
    parms.retrans_effort = p->esco.setup.retrans_effort;

    return (BTM_ChangeEScoLinkParms(sco_inx, &parms));
#else
    return (BTM_UNKNOWN_ADDR);
#endif
}