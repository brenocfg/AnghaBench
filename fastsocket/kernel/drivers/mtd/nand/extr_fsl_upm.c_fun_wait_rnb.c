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
struct fsl_upm_nand {scalar_t__* rnb_gpio; size_t mchip_number; int /*<<< orphan*/  dev; int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fun_chip_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void fun_wait_rnb(struct fsl_upm_nand *fun)
{
	if (fun->rnb_gpio[fun->mchip_number] >= 0) {
		int cnt = 1000000;

		while (--cnt && !fun_chip_ready(&fun->mtd))
			cpu_relax();
		if (!cnt)
			dev_err(fun->dev, "tired waiting for RNB\n");
	} else {
		ndelay(100);
	}
}