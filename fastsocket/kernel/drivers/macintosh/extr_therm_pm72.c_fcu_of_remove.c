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
struct of_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  therm_pm72_driver ; 

__attribute__((used)) static int fcu_of_remove(struct of_device* dev)
{
	i2c_del_driver(&therm_pm72_driver);

	return 0;
}