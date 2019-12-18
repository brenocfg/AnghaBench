#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stu300_dev {int speed; scalar_t__ virtbase; TYPE_1__* pdev; } ;
struct TYPE_5__ {unsigned long rate; int setting; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ I2C_CCR ; 
 int I2C_CCR_CC_MASK ; 
 int I2C_CCR_FMSM ; 
 scalar_t__ I2C_ECCR ; 
 scalar_t__ I2C_OAR2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* stu300_clktable ; 
 int /*<<< orphan*/  stu300_wr8 (int,scalar_t__) ; 

__attribute__((used)) static int stu300_set_clk(struct stu300_dev *dev, unsigned long clkrate)
{

	u32 val;
	int i = 0;

	/* Locate the apropriate clock setting */
	while (i < ARRAY_SIZE(stu300_clktable) &&
	       stu300_clktable[i].rate < clkrate)
		i++;

	if (stu300_clktable[i].setting == 0xFFU) {
		dev_err(&dev->pdev->dev, "too %s clock rate requested "
			"(%lu Hz).\n", i ? "high" : "low", clkrate);
		return -EINVAL;
	}

	stu300_wr8(stu300_clktable[i].setting,
		   dev->virtbase + I2C_OAR2);

	dev_dbg(&dev->pdev->dev, "Clock rate %lu Hz, I2C bus speed %d Hz "
		"virtbase %p\n", clkrate, dev->speed, dev->virtbase);

	if (dev->speed > 100000)
		/* Fast Mode I2C */
		val = ((clkrate/dev->speed) - 9)/3 + 1;
	else
		/* Standard Mode I2C */
		val = ((clkrate/dev->speed) - 7)/2 + 1;

	/* According to spec the divider must be > 2 */
	if (val < 0x002) {
		dev_err(&dev->pdev->dev, "too low clock rate (%lu Hz).\n",
			clkrate);
		return -EINVAL;
	}

	/* We have 12 bits clock divider only! */
	if (val & 0xFFFFF000U) {
		dev_err(&dev->pdev->dev, "too high clock rate (%lu Hz).\n",
			clkrate);
		return -EINVAL;
	}

	if (dev->speed > 100000) {
		/* CC6..CC0 */
		stu300_wr8((val & I2C_CCR_CC_MASK) | I2C_CCR_FMSM,
			   dev->virtbase + I2C_CCR);
		dev_dbg(&dev->pdev->dev, "set clock divider to 0x%08x, "
			"Fast Mode I2C\n", val);
	} else {
		/* CC6..CC0 */
		stu300_wr8((val & I2C_CCR_CC_MASK),
			   dev->virtbase + I2C_CCR);
		dev_dbg(&dev->pdev->dev, "set clock divider to "
			"0x%08x, Standard Mode I2C\n", val);
	}

	/* CC11..CC7 */
	stu300_wr8(((val >> 7) & 0x1F),
		   dev->virtbase + I2C_ECCR);

	return 0;
}