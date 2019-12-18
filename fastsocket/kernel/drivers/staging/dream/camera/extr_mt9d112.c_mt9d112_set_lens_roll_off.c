#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rftbl_size; int /*<<< orphan*/ * rftbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt9d112_i2c_write_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ mt9d112_regs ; 

__attribute__((used)) static int32_t mt9d112_set_lens_roll_off(void)
{
	int32_t rc = 0;
	rc = mt9d112_i2c_write_table(&mt9d112_regs.rftbl[0],
								 mt9d112_regs.rftbl_size);
	return rc;
}