#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; } ;
typedef  TYPE_2__ tSCO_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_2__* sco_db; } ;
struct TYPE_6__ {TYPE_1__ sco_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_MAX_SCO_LINKS ; 
#define  SCO_ST_CONNECTED 132 
#define  SCO_ST_CONNECTING 131 
#define  SCO_ST_DISCONNECTING 130 
#define  SCO_ST_PEND_UNPARK 129 
#define  SCO_ST_W4_CONN_RSP 128 
 TYPE_3__ btm_cb ; 

UINT8 BTM_GetNumScoLinks (void)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN *p = &btm_cb.sco_cb.sco_db[0];
    UINT16     xx;
    UINT8      num_scos = 0;

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        switch (p->state) {
        case SCO_ST_W4_CONN_RSP:
        case SCO_ST_CONNECTING:
        case SCO_ST_CONNECTED:
        case SCO_ST_DISCONNECTING:
        case SCO_ST_PEND_UNPARK:
            num_scos++;
        }
    }
    return (num_scos);
#else
    return (0);
#endif
}