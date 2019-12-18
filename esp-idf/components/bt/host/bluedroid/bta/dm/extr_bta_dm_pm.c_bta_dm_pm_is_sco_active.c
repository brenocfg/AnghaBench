#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; TYPE_1__* conn_srvc; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BTA_ID_AG ; 
 scalar_t__ BTA_SYS_SCO_OPEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ bta_dm_conn_srvcs ; 

__attribute__((used)) static BOOLEAN bta_dm_pm_is_sco_active (void)
{
    int j;
    BOOLEAN bScoActive = FALSE;

    for (j = 0; j < bta_dm_conn_srvcs.count ; j++) {
        /* check if an entry already present */
        if ( (bta_dm_conn_srvcs.conn_srvc[j].id == BTA_ID_AG )  && (bta_dm_conn_srvcs.conn_srvc[j].state == BTA_SYS_SCO_OPEN) ) {
            bScoActive = TRUE;
            break;
        }
    }

    APPL_TRACE_DEBUG("bta_dm_is_sco_active: SCO active: %d", bScoActive);
    return bScoActive;
}