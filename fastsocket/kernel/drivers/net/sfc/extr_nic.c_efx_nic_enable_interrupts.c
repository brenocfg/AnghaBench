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
struct TYPE_2__ {scalar_t__ addr; } ;
struct efx_nic {TYPE_1__ irq_status; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_interrupts (struct efx_nic*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

void efx_nic_enable_interrupts(struct efx_nic *efx)
{
	EFX_ZERO_OWORD(*((efx_oword_t *) efx->irq_status.addr));
	wmb(); /* Ensure interrupt vector is clear before interrupts enabled */

	efx_nic_interrupts(efx, true, false);
}