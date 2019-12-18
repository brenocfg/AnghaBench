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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long GPSELEI0 ; 
 unsigned long GPSELEI1 ; 
 int /*<<< orphan*/  REG_MFSEL ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mfp_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void mfp_set_groupi(struct device *dev)
{
	unsigned long mfpen;
	const char *dev_id;

	BUG_ON(!dev);

	mutex_lock(&mfp_mutex);

	dev_id = dev_name(dev);

	mfpen = __raw_readl(REG_MFSEL);

	mfpen &= ~GPSELEI1;/*default gpio16*/

	if (strcmp(dev_id, "nuc900-wdog") == 0)
		mfpen |= GPSELEI1;/*enable wdog*/
	else if (strcmp(dev_id, "nuc900-atapi") == 0)
		mfpen |= GPSELEI0;/*enable atapi*/
	else if (strcmp(dev_id, "nuc900-keypad") == 0)
		mfpen &= ~GPSELEI0;/*enable keypad*/

	__raw_writel(mfpen, REG_MFSEL);

	mutex_unlock(&mfp_mutex);
}