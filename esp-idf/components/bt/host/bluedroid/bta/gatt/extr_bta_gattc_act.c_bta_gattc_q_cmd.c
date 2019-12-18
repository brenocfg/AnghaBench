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
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  bta_gattc_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bta_gattc_q_cmd(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    bta_gattc_enqueue(p_clcb, p_data);
}