#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  scalar_t__ UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/ * scb; } ;

/* Variables and functions */
 TYPE_1__ bta_ag_cb ; 

UINT16 bta_ag_scb_to_idx(tBTA_AG_SCB *p_scb)
{
    /* use array arithmetic to determine index */
    return ((UINT16) (p_scb - bta_ag_cb.scb)) + 1;
}