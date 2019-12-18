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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  lctbl_size; int /*<<< orphan*/  lctbl; } ;

/* Variables and functions */
 scalar_t__ mt9t013_i2c_write_w_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ mt9t013_regs ; 

__attribute__((used)) static int32_t mt9t013_set_lc(void)
{
	int32_t rc;

	rc = mt9t013_i2c_write_w_table(mt9t013_regs.lctbl, mt9t013_regs.lctbl_size);
	if (rc < 0)
		return rc;

	return rc;
}