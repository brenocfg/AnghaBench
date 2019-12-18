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
struct w90p910_nand {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int READYBUSY ; 
 int /*<<< orphan*/  REG_SMISR ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int w90p910_check_rb(struct w90p910_nand *nand)
{
	unsigned int val;
	spin_lock(&nand->lock);
	val = __raw_readl(REG_SMISR);
	val &= READYBUSY;
	spin_unlock(&nand->lock);

	return val;
}