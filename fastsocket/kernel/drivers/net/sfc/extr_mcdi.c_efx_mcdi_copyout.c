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
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int FR_CZ_MC_TREG_SMEM ; 
 unsigned int MCDI_PDU (struct efx_nic*) ; 
 scalar_t__ MCDI_STATE_QUIESCENT ; 
 size_t MC_SMEM_PDU_LEN ; 
 int /*<<< orphan*/  _efx_readd (struct efx_nic*,unsigned int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 

__attribute__((used)) static void efx_mcdi_copyout(struct efx_nic *efx, u8 *outbuf, size_t outlen)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	unsigned int pdu = FR_CZ_MC_TREG_SMEM + MCDI_PDU(efx);
	int i;

	BUG_ON(atomic_read(&mcdi->state) == MCDI_STATE_QUIESCENT);
	BUG_ON(outlen & 3 || outlen >= MC_SMEM_PDU_LEN);

	for (i = 0; i < outlen; i += 4)
		*((__le32 *)(outbuf + i)) = _efx_readd(efx, pdu + 4 + i);
}