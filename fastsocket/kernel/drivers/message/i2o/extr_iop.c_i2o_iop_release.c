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
struct i2o_controller {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_iop_free (struct i2o_controller*) ; 
 struct i2o_controller* to_i2o_controller (struct device*) ; 

__attribute__((used)) static void i2o_iop_release(struct device *dev)
{
	struct i2o_controller *c = to_i2o_controller(dev);

	i2o_iop_free(c);
}