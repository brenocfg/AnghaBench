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
struct TYPE_6__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * p_esco_cback; TYPE_1__ data; } ;
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  (* p_disc_cb ) (scalar_t__) ;TYPE_2__ esco; scalar_t__ rem_bd_known; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {TYPE_4__* sco_db; } ;
struct TYPE_10__ {TYPE_3__ sco_cb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 scalar_t__ SCO_ST_UNUSED ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btm_sco_flush_sco_data (scalar_t__) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void btm_sco_acl_removed (BD_ADDR bda)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[0];
    UINT16      xx;

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if (p->state != SCO_ST_UNUSED) {
            if ((!bda) || (!memcmp (p->esco.data.bd_addr, bda, BD_ADDR_LEN) && p->rem_bd_known)) {
                btm_sco_flush_sco_data(xx);

                p->state = SCO_ST_UNUSED;
                p->esco.p_esco_cback = NULL;    /* Deregister eSCO callback */
                (*p->p_disc_cb)(xx);
            }
        }
    }
#endif
}