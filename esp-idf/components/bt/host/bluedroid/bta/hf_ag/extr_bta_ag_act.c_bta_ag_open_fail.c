#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_FAIL_RESOURCES ; 
 int /*<<< orphan*/  bta_ag_cback_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_ag_open_fail(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    /* call open cback w. failure */
    bta_ag_cback_open(p_scb, p_data, BTA_AG_FAIL_RESOURCES);
}