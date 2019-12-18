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
struct hw_data {int /*<<< orphan*/  LEDTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Rx_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Tx_destroy (struct hw_data*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void hal_halt(struct hw_data *pHwData)
{
	del_timer_sync(&pHwData->LEDTimer);
	/* XXX: Wait for Timer DPC exit. */
	msleep(100);
	Wb35Rx_destroy(pHwData);
	Wb35Tx_destroy(pHwData);
	Wb35Reg_destroy(pHwData);
}