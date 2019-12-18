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
typedef  int u32 ;
struct mc13783 {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int mc13783_read (struct mc13783*,int,int*) ; 
 int mc13783_write (struct mc13783*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mc13783_set_bits(struct mc13783 *mc13783, int reg, u32 mask, u32 val)
{
	u32 tmp;
	int ret;

	mutex_lock(&mc13783->io_lock);

	ret = mc13783_read(mc13783, reg, &tmp);
	tmp = (tmp & ~mask) | val;
	if (ret == 0)
		ret = mc13783_write(mc13783, reg, tmp);

	mutex_unlock(&mc13783->io_lock);

	return ret;
}