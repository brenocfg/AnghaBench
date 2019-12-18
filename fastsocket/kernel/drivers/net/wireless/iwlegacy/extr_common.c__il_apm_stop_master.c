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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_MASTER_DISABLED ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_STOP_MASTER ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_il_apm_stop_master(struct il_priv *il)
{
	int ret = 0;

	/* stop device's busmaster DMA activity */
	_il_set_bit(il, CSR_RESET, CSR_RESET_REG_FLAG_STOP_MASTER);

	ret =
	    _il_poll_bit(il, CSR_RESET, CSR_RESET_REG_FLAG_MASTER_DISABLED,
			 CSR_RESET_REG_FLAG_MASTER_DISABLED, 100);
	if (ret < 0)
		IL_WARN("Master Disable Timed Out, 100 usec\n");

	D_INFO("stop master\n");

	return ret;
}