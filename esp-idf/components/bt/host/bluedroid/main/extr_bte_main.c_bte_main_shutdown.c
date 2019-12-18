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
 int /*<<< orphan*/  BTA_VendorCleanup () ; 
 int /*<<< orphan*/  bte_main_disable () ; 
 int /*<<< orphan*/  osi_deinit () ; 

void bte_main_shutdown(void)
{
#if (BLE_INCLUDED == TRUE)
    BTA_VendorCleanup();
#endif
    bte_main_disable();

    osi_deinit();
}