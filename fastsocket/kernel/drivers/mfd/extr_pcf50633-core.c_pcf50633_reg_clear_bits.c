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
typedef  int /*<<< orphan*/  u8 ;
struct pcf50633 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __pcf50633_read (struct pcf50633*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int __pcf50633_write (struct pcf50633*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int pcf50633_reg_clear_bits(struct pcf50633 *pcf, u8 reg, u8 val)
{
	int ret;
	u8 tmp;

	mutex_lock(&pcf->lock);
	ret = __pcf50633_read(pcf, reg, 1, &tmp);
	if (ret < 0)
		goto out;

	tmp &= ~val;
	ret = __pcf50633_write(pcf, reg, 1, &tmp);

out:
	mutex_unlock(&pcf->lock);

	return ret;
}