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
struct mc13783 {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int mc13783_read (struct mc13783*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mc13783_reg_read(struct mc13783 *mc13783, int reg_num, u32 *reg_val)
{
	int ret;

	mutex_lock(&mc13783->io_lock);
	ret = mc13783_read(mc13783, reg_num, reg_val);
	mutex_unlock(&mc13783->io_lock);

	return ret;
}