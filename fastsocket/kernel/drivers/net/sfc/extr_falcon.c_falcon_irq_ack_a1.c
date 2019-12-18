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
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AA_INT_ACK_KER_FIELD ; 
 int /*<<< orphan*/  FR_AA_INT_ACK_KER ; 
 int /*<<< orphan*/  FR_AA_WORK_AROUND_BROKEN_PCI_READS ; 
 int /*<<< orphan*/  efx_readd (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

inline void falcon_irq_ack_a1(struct efx_nic *efx)
{
	efx_dword_t reg;

	EFX_POPULATE_DWORD_1(reg, FRF_AA_INT_ACK_KER_FIELD, 0xb7eb7e);
	efx_writed(efx, &reg, FR_AA_INT_ACK_KER);
	efx_readd(efx, &reg, FR_AA_WORK_AROUND_BROKEN_PCI_READS);
}