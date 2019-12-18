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
struct budget {int /*<<< orphan*/  i2c_adap; } ;
struct budget_av {int has_saa7113; int cur_input; struct budget budget; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  i2c_writereg (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int saa7113_setinput(struct budget_av *budget_av, int input)
{
	struct budget *budget = &budget_av->budget;

	if (1 != budget_av->has_saa7113)
		return -ENODEV;

	if (input == 1) {
		i2c_writereg(&budget->i2c_adap, 0x4a, 0x02, 0xc7);
		i2c_writereg(&budget->i2c_adap, 0x4a, 0x09, 0x80);
	} else if (input == 0) {
		i2c_writereg(&budget->i2c_adap, 0x4a, 0x02, 0xc0);
		i2c_writereg(&budget->i2c_adap, 0x4a, 0x09, 0x00);
	} else
		return -EINVAL;

	budget_av->cur_input = input;
	return 0;
}