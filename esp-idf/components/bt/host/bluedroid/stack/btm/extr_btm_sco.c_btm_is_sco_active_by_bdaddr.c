#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_3__ esco; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  scalar_t__ UINT8 ;
struct TYPE_6__ {TYPE_4__* sco_db; } ;
struct TYPE_10__ {TYPE_1__ sco_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCO_ST_CONNECTED ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN btm_is_sco_active_by_bdaddr (BD_ADDR remote_bda)
{
#if (BTM_MAX_SCO_LINKS>0)
    UINT8 xx;
    tSCO_CONN *p = &btm_cb.sco_cb.sco_db[0];

    /* If any SCO is being established to the remote BD address, refuse this */
    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if ((!memcmp (p->esco.data.bd_addr, remote_bda, BD_ADDR_LEN)) && (p->state == SCO_ST_CONNECTED)) {
            return (TRUE);
        }
    }
#endif
    return (FALSE);
}