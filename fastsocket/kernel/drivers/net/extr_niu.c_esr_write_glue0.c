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
typedef  int u32 ;
struct niu {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_GLUE_CTRL0_H (unsigned long) ; 
 int /*<<< orphan*/  ESR_GLUE_CTRL0_L (unsigned long) ; 
 int /*<<< orphan*/  NIU_ESR_DEV_ADDR ; 
 int mdio_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esr_write_glue0(struct niu *np, unsigned long chan, u32 val)
{
	int err;

	err = mdio_write(np, np->port, NIU_ESR_DEV_ADDR,
			ESR_GLUE_CTRL0_L(chan), val & 0xffff);
	if (!err)
		err = mdio_write(np, np->port, NIU_ESR_DEV_ADDR,
				 ESR_GLUE_CTRL0_H(chan), (val >> 16));
	return err;
}