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
typedef  int /*<<< orphan*/  outbuf ;
typedef  int /*<<< orphan*/  inbuf ;

/* Variables and functions */
 int EIO ; 
 int MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_NVRAM_TEST ; 
 int MC_CMD_NVRAM_TEST_IN_LEN ; 
#define  MC_CMD_NVRAM_TEST_NOTSUPP 129 
 int MC_CMD_NVRAM_TEST_OUT_LEN ; 
#define  MC_CMD_NVRAM_TEST_PASS 128 
 int /*<<< orphan*/  NVRAM_TEST_IN_TYPE ; 
 int /*<<< orphan*/  NVRAM_TEST_OUT_RESULT ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_mcdi_nvram_test(struct efx_nic *efx, unsigned int type)
{
	u8 inbuf[MC_CMD_NVRAM_TEST_IN_LEN];
	u8 outbuf[MC_CMD_NVRAM_TEST_OUT_LEN];
	int rc;

	MCDI_SET_DWORD(inbuf, NVRAM_TEST_IN_TYPE, type);

	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_TEST, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), NULL);
	if (rc)
		return rc;

	switch (MCDI_DWORD(outbuf, NVRAM_TEST_OUT_RESULT)) {
	case MC_CMD_NVRAM_TEST_PASS:
	case MC_CMD_NVRAM_TEST_NOTSUPP:
		return 0;
	default:
		return -EIO;
	}
}