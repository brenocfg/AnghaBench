#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {TYPE_2__* ptp_data; } ;
typedef  int /*<<< orphan*/  inbuf ;
struct TYPE_4__ {int /*<<< orphan*/  mode; TYPE_1__* channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_CMD_PTP ; 
 int MC_CMD_PTP_IN_ENABLE_LEN ; 
 int /*<<< orphan*/  MC_CMD_PTP_OP_ENABLE ; 
 int /*<<< orphan*/  PTP_IN_ENABLE_MODE ; 
 int /*<<< orphan*/  PTP_IN_ENABLE_QUEUE ; 
 int /*<<< orphan*/  PTP_IN_OP ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ptp_enable(struct efx_nic *efx)
{
	u8 inbuf[MC_CMD_PTP_IN_ENABLE_LEN];

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_ENABLE);
	MCDI_SET_DWORD(inbuf, PTP_IN_ENABLE_QUEUE,
		       efx->ptp_data->channel->channel);
	MCDI_SET_DWORD(inbuf, PTP_IN_ENABLE_MODE, efx->ptp_data->mode);

	return efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, sizeof(inbuf),
			    NULL, 0, NULL);
}