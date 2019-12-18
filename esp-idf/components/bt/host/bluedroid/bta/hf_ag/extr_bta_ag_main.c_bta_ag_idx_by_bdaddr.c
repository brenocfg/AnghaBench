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
struct TYPE_3__ {int /*<<< orphan*/  peer_addr; scalar_t__ in_use; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_1__* scb; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*) ; 
 scalar_t__ BTA_AG_NUM_SCB ; 
 int /*<<< orphan*/  bdcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ bta_ag_cb ; 

UINT16 bta_ag_idx_by_bdaddr(BD_ADDR peer_addr)
{
    tBTA_AG_SCB     *p_scb = &bta_ag_cb.scb[0];
    UINT16          i;

    if (peer_addr != NULL) {
        for (i = 0; i < BTA_AG_NUM_SCB; i++, p_scb++) {
            if (p_scb->in_use && !bdcmp(peer_addr, p_scb->peer_addr)) {
                return (i + 1);
            }
        }
    }
    /* no scb found */
    APPL_TRACE_WARNING("No ag scb for peer addr");
    return 0;
}