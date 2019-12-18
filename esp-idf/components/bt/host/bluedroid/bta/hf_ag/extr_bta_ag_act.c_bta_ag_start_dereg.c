#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dealloc; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_ag_del_records (TYPE_1__*,int /*<<< orphan*/ *) ; 

void bta_ag_start_dereg(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    /* set dealloc */
    p_scb->dealloc = TRUE;
    /* remove sdp records */
    bta_ag_del_records(p_scb, p_data);
}