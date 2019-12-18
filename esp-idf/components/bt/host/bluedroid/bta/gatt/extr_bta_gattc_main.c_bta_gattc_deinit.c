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
typedef  int /*<<< orphan*/  tBTA_GATTC_CB ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_gattc_cb_ptr ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void bta_gattc_deinit(void)
{
#if BTA_DYNAMIC_MEMORY
    memset(bta_gattc_cb_ptr, 0, sizeof(tBTA_GATTC_CB));
    FREE_AND_RESET(bta_gattc_cb_ptr);
#endif /* #if BTA_DYNAMIC_MEMORY */
}