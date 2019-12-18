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
struct cmac_statistics {int dummy; } ;
struct cmac {int /*<<< orphan*/  adapter; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNI1x10GEXP_BITMSK_MSTAT_CLEAR ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_MSTAT_CONTROL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm3393_enable (struct cmac*,int) ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_link_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pm3393_enable_port(struct cmac *cmac, int which)
{
	/* Clear port statistics */
	pmwrite(cmac, SUNI1x10GEXP_REG_MSTAT_CONTROL,
		SUNI1x10GEXP_BITMSK_MSTAT_CLEAR);
	udelay(2);
	memset(&cmac->stats, 0, sizeof(struct cmac_statistics));

	pm3393_enable(cmac, which);

	/*
	 * XXX This should be done by the PHY and preferrably not at all.
	 * The PHY doesn't give us link status indication on its own so have
	 * the link management code query it instead.
	 */
	t1_link_changed(cmac->adapter, 0);
	return 0;
}