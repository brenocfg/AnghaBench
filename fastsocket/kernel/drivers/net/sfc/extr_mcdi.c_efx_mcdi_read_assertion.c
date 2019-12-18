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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  outbuf ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  GET_ASSERTS_IN_CLEAR ; 
 int /*<<< orphan*/  GET_ASSERTS_OUT_GLOBAL_FLAGS ; 
 int /*<<< orphan*/  GET_ASSERTS_OUT_SAVED_PC_OFFS ; 
 int /*<<< orphan*/  GET_ASSERTS_OUT_THREAD_OFFS ; 
 unsigned int MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_DWORD2 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MC_CMD_GET_ASSERTS ; 
 unsigned int MC_CMD_GET_ASSERTS_FLAGS_NO_FAILS ; 
 unsigned int MC_CMD_GET_ASSERTS_FLAGS_SYS_FAIL ; 
 unsigned int MC_CMD_GET_ASSERTS_FLAGS_THR_FAIL ; 
 unsigned int MC_CMD_GET_ASSERTS_FLAGS_WDOG_FIRED ; 
 int MC_CMD_GET_ASSERTS_IN_LEN ; 
 unsigned int MC_CMD_GET_ASSERTS_OUT_GP_REGS_OFFS_OFST ; 
 int MC_CMD_GET_ASSERTS_OUT_LEN ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int efx_mcdi_read_assertion(struct efx_nic *efx)
{
	u8 inbuf[MC_CMD_GET_ASSERTS_IN_LEN];
	u8 outbuf[MC_CMD_GET_ASSERTS_OUT_LEN];
	unsigned int flags, index, ofst;
	const char *reason;
	size_t outlen;
	int retry;
	int rc;

	/* Attempt to read any stored assertion state before we reboot
	 * the mcfw out of the assertion handler. Retry twice, once
	 * because a boot-time assertion might cause this command to fail
	 * with EINTR. And once again because GET_ASSERTS can race with
	 * MC_CMD_REBOOT running on the other port. */
	retry = 2;
	do {
		MCDI_SET_DWORD(inbuf, GET_ASSERTS_IN_CLEAR, 1);
		rc = efx_mcdi_rpc(efx, MC_CMD_GET_ASSERTS,
				  inbuf, MC_CMD_GET_ASSERTS_IN_LEN,
				  outbuf, sizeof(outbuf), &outlen);
	} while ((rc == -EINTR || rc == -EIO) && retry-- > 0);

	if (rc)
		return rc;
	if (outlen < MC_CMD_GET_ASSERTS_OUT_LEN)
		return -EIO;

	/* Print out any recorded assertion state */
	flags = MCDI_DWORD(outbuf, GET_ASSERTS_OUT_GLOBAL_FLAGS);
	if (flags == MC_CMD_GET_ASSERTS_FLAGS_NO_FAILS)
		return 0;

	reason = (flags == MC_CMD_GET_ASSERTS_FLAGS_SYS_FAIL)
		? "system-level assertion"
		: (flags == MC_CMD_GET_ASSERTS_FLAGS_THR_FAIL)
		? "thread-level assertion"
		: (flags == MC_CMD_GET_ASSERTS_FLAGS_WDOG_FIRED)
		? "watchdog reset"
		: "unknown assertion";
	netif_err(efx, hw, efx->net_dev,
		  "MCPU %s at PC = 0x%.8x in thread 0x%.8x\n", reason,
		  MCDI_DWORD(outbuf, GET_ASSERTS_OUT_SAVED_PC_OFFS),
		  MCDI_DWORD(outbuf, GET_ASSERTS_OUT_THREAD_OFFS));

	/* Print out the registers */
	ofst = MC_CMD_GET_ASSERTS_OUT_GP_REGS_OFFS_OFST;
	for (index = 1; index < 32; index++) {
		netif_err(efx, hw, efx->net_dev, "R%.2d (?): 0x%.8x\n", index,
			MCDI_DWORD2(outbuf, ofst));
		ofst += sizeof(efx_dword_t);
	}

	return 0;
}