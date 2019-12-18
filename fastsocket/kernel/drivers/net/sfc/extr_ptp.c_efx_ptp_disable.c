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
typedef  int /*<<< orphan*/  inbuf ;

/* Variables and functions */
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_CMD_PTP ; 
 int MC_CMD_PTP_IN_DISABLE_LEN ; 
 int /*<<< orphan*/  MC_CMD_PTP_OP_DISABLE ; 
 int /*<<< orphan*/  PTP_IN_OP ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ptp_disable(struct efx_nic *efx)
{
	u8 inbuf[MC_CMD_PTP_IN_DISABLE_LEN];

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_DISABLE);
	return efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, sizeof(inbuf),
			    NULL, 0, NULL);
}