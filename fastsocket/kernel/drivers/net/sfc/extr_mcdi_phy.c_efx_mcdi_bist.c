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
typedef  scalar_t__ u32 ;
struct efx_nic {scalar_t__ phy_type; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_DWORD_0 ; 
 int EFX_DWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MCDI_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int MC_CMD_PHY_BIST_CABLE_LONG ; 
 unsigned int MC_CMD_PHY_BIST_CABLE_SHORT ; 
 int /*<<< orphan*/  MC_CMD_POLL_BIST ; 
 scalar_t__ MC_CMD_POLL_BIST_IN_LEN ; 
 size_t MC_CMD_POLL_BIST_OUT_SFT9001_LEN ; 
 scalar_t__ MC_CMD_POLL_BIST_PASSED ; 
 scalar_t__ MC_CMD_POLL_BIST_RUNNING ; 
 int /*<<< orphan*/  MC_CMD_START_BIST ; 
 int /*<<< orphan*/  MC_CMD_START_BIST_IN_LEN ; 
 scalar_t__ MC_CMD_START_BIST_OUT_LEN ; 
 scalar_t__ PHY_TYPE_SFT9001B ; 
 int /*<<< orphan*/  POLL_BIST_OUT_RESULT ; 
 int /*<<< orphan*/  POLL_BIST_OUT_SFT9001_CABLE_LENGTH_A ; 
 int /*<<< orphan*/  START_BIST_IN_TYPE ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int efx_mcdi_bist(struct efx_nic *efx, unsigned int bist_mode,
			 int *results)
{
	unsigned int retry, i, count = 0;
	size_t outlen;
	u32 status;
	u8 *buf, *ptr;
	int rc;

	buf = kzalloc(0x100, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	BUILD_BUG_ON(MC_CMD_START_BIST_OUT_LEN != 0);
	MCDI_SET_DWORD(buf, START_BIST_IN_TYPE, bist_mode);
	rc = efx_mcdi_rpc(efx, MC_CMD_START_BIST, buf, MC_CMD_START_BIST_IN_LEN,
			  NULL, 0, NULL);
	if (rc)
		goto out;

	/* Wait up to 10s for BIST to finish */
	for (retry = 0; retry < 100; ++retry) {
		BUILD_BUG_ON(MC_CMD_POLL_BIST_IN_LEN != 0);
		rc = efx_mcdi_rpc(efx, MC_CMD_POLL_BIST, NULL, 0,
				  buf, 0x100, &outlen);
		if (rc)
			goto out;

		status = MCDI_DWORD(buf, POLL_BIST_OUT_RESULT);
		if (status != MC_CMD_POLL_BIST_RUNNING)
			goto finished;

		msleep(100);
	}

	rc = -ETIMEDOUT;
	goto out;

finished:
	results[count++] = (status == MC_CMD_POLL_BIST_PASSED) ? 1 : -1;

	/* SFT9001 specific cable diagnostics output */
	if (efx->phy_type == PHY_TYPE_SFT9001B &&
	    (bist_mode == MC_CMD_PHY_BIST_CABLE_SHORT ||
	     bist_mode == MC_CMD_PHY_BIST_CABLE_LONG)) {
		ptr = MCDI_PTR(buf, POLL_BIST_OUT_SFT9001_CABLE_LENGTH_A);
		if (status == MC_CMD_POLL_BIST_PASSED &&
		    outlen >= MC_CMD_POLL_BIST_OUT_SFT9001_LEN) {
			for (i = 0; i < 8; i++) {
				results[count + i] =
					EFX_DWORD_FIELD(((efx_dword_t *)ptr)[i],
							EFX_DWORD_0);
			}
		}
		count += 8;
	}
	rc = count;

out:
	kfree(buf);

	return rc;
}