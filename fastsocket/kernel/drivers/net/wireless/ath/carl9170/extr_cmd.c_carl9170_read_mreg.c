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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ar9170 {TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_RREG ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

int carl9170_read_mreg(struct ar9170 *ar, const int nregs,
		       const u32 *regs, u32 *out)
{
	int i, err;
	__le32 *offs, *res;

	/* abuse "out" for the register offsets, must be same length */
	offs = (__le32 *)out;
	for (i = 0; i < nregs; i++)
		offs[i] = cpu_to_le32(regs[i]);

	/* also use the same buffer for the input */
	res = (__le32 *)out;

	err = carl9170_exec_cmd(ar, CARL9170_CMD_RREG,
				4 * nregs, (u8 *)offs,
				4 * nregs, (u8 *)res);
	if (err) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "reading regs failed (%d)\n",
				  err);
		}
		return err;
	}

	/* convert result to cpu endian */
	for (i = 0; i < nregs; i++)
		out[i] = le32_to_cpu(res[i]);

	return 0;
}