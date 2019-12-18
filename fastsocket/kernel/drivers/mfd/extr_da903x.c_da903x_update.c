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
typedef  int uint8_t ;
struct device {int dummy; } ;
struct da903x_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int __da903x_read (int /*<<< orphan*/ ,int,int*) ; 
 int __da903x_write (int /*<<< orphan*/ ,int,int) ; 
 struct da903x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int da903x_update(struct device *dev, int reg, uint8_t val, uint8_t mask)
{
	struct da903x_chip *chip = dev_get_drvdata(dev);
	uint8_t reg_val;
	int ret = 0;

	mutex_lock(&chip->lock);

	ret = __da903x_read(chip->client, reg, &reg_val);
	if (ret)
		goto out;

	if ((reg_val & mask) != val) {
		reg_val = (reg_val & ~mask) | val;
		ret = __da903x_write(chip->client, reg, reg_val);
	}
out:
	mutex_unlock(&chip->lock);
	return ret;
}