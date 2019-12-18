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
 int /*<<< orphan*/  IOP13XX_ATUE_OCCAR ; 
 int /*<<< orphan*/  IOP13XX_ATUE_OCCDR ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static u32 iop13xx_atue_read(unsigned long addr)
{
	u32 val;

	__raw_writel(addr, IOP13XX_ATUE_OCCAR);
	val = __raw_readl(IOP13XX_ATUE_OCCDR);

	rmb();

	return val;
}