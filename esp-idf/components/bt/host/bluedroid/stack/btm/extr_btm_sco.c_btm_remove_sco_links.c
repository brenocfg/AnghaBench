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
struct TYPE_9__ {TYPE_3__ esco; scalar_t__ rem_bd_known; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {TYPE_4__* sco_db; } ;
struct TYPE_10__ {TYPE_1__ sco_cb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_RemoveSco (scalar_t__) ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_remove_sco_links (BD_ADDR bda)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[0];
    UINT16       xx;

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if (p->rem_bd_known && (!memcmp (p->esco.data.bd_addr, bda, BD_ADDR_LEN))) {
            BTM_RemoveSco(xx);
        }
    }
#endif
}