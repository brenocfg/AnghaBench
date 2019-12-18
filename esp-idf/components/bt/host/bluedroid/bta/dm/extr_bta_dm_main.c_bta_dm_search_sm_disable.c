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

/* Variables and functions */
 int /*<<< orphan*/  BTA_ID_DM_SEARCH ; 
 int /*<<< orphan*/  bta_sys_deregister (int /*<<< orphan*/ ) ; 

void bta_dm_search_sm_disable(void)
{
    bta_sys_deregister( BTA_ID_DM_SEARCH );

}