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
struct regulator_init_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* add_regulator_linked (int,struct regulator_init_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *
add_regulator(int num, struct regulator_init_data *pdata)
{
	return add_regulator_linked(num, pdata, NULL, 0);
}