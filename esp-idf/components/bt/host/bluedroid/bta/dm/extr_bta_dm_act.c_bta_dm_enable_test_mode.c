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
typedef  int /*<<< orphan*/  tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_EnableTestMode () ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 

void bta_dm_enable_test_mode(tBTA_DM_MSG *p_data)
{
    UNUSED(p_data);
    BTM_EnableTestMode();
}