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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  OMAP2_IO_ADDRESS (scalar_t__) ; 
 scalar_t__ OMAP_32KSYNCT_BASE ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_class_is_omap2 () ; 

__attribute__((used)) static u32 _read_32ksynct(void)
{
	if (!cpu_class_is_omap2())
		BUG();

	return __raw_readl(OMAP2_IO_ADDRESS(OMAP_32KSYNCT_BASE + 0x010));
}