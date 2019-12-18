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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
 int EBUSY ; 
 int LI_CC_BUSY ; 
 int /*<<< orphan*/  LI_CODEC_COMMAND ; 
 int jiffies ; 
 int li_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

__attribute__((used)) static int li_ad1843_wait(lithium_t *lith)
{
	unsigned long later = jiffies + 2;
	while (li_readl(lith, LI_CODEC_COMMAND) & LI_CC_BUSY)
		if (time_after_eq(jiffies, later))
			return -EBUSY;
	return 0;
}