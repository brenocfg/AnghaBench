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
struct TYPE_5__ {scalar_t__ hci_handle; scalar_t__ state; } ;
typedef  TYPE_2__ tSCO_CONN ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_2__* sco_db; } ;
struct TYPE_6__ {TYPE_1__ sco_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCO_ST_CONNECTED ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ btm_cb ; 

BOOLEAN btm_is_sco_active (UINT16 handle)
{
#if (BTM_MAX_SCO_LINKS>0)
    UINT16     xx;
    tSCO_CONN *p = &btm_cb.sco_cb.sco_db[0];

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if (handle == p->hci_handle && p->state == SCO_ST_CONNECTED) {
            return (TRUE);
        }
    }
#endif
    return (FALSE);
}