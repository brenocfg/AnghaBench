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
struct efx_nic {int last_irq_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_interrupts (struct efx_nic*,int,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void efx_nic_irq_test_start(struct efx_nic *efx)
{
	efx->last_irq_cpu = -1;
	smp_wmb();
	efx_nic_interrupts(efx, true, true);
}