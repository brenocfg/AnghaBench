#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ lithium_t ;

/* Variables and functions */
 int LI_CC_DIR_WR ; 
 int /*<<< orphan*/  LI_CODEC_COMMAND ; 
 int /*<<< orphan*/  LI_CODEC_DATA ; 
 scalar_t__ li_ad1843_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  li_writel (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void li_write_ad1843_reg(lithium_t *lith, int reg, int newval)
{
	spin_lock(&lith->lock);
	{
		if (li_ad1843_wait(lith) == 0) {
			li_writel(lith, LI_CODEC_DATA, newval);
			li_writel(lith, LI_CODEC_COMMAND, LI_CC_DIR_WR | reg);
		}
	}
	spin_unlock(&lith->lock);
}