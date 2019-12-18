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

__attribute__((weak)) void emac_hal_rx_early_cb(void *arg)
{
    // This is a weak function, do nothing by default
    // Upper code can rewrite this function
    // Note: you're in the interrupt context
    return;
}