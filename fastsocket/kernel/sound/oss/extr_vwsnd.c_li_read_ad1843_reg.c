#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ lithium_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBGXV (char*,TYPE_1__*,int,int) ; 
 int LI_CC_DIR_RD ; 
 int /*<<< orphan*/  LI_CODEC_COMMAND ; 
 int /*<<< orphan*/  LI_CODEC_DATA ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int li_ad1843_wait (TYPE_1__*) ; 
 int li_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  li_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int li_read_ad1843_reg(lithium_t *lith, int reg)
{
	int val;

	ASSERT(!in_interrupt());
	spin_lock(&lith->lock);
	{
		val = li_ad1843_wait(lith);
		if (val == 0) {
			li_writel(lith, LI_CODEC_COMMAND, LI_CC_DIR_RD | reg);
			val = li_ad1843_wait(lith);
		}
		if (val == 0)
			val = li_readl(lith, LI_CODEC_DATA);
	}
	spin_unlock(&lith->lock);

	DBGXV("li_read_ad1843_reg(lith=0x%p, reg=%d) returns 0x%04x\n",
	      lith, reg, val);

	return val;
}