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

/* Variables and functions */
 int /*<<< orphan*/  i2o_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2o_exec_driver ; 

void i2o_exec_exit(void)
{
	i2o_driver_unregister(&i2o_exec_driver);
}