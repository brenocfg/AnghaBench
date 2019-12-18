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
struct s5k3e2fx_i2c_reg_conf {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ EIO ; 

__attribute__((used)) static int32_t s5k3e2fx_i2c_write_table(
	struct s5k3e2fx_i2c_reg_conf *reg_cfg_tbl, int num)
{
	int i;
	int32_t rc = -EIO;
	for (i = 0; i < num; i++) {
		if (rc < 0)
			break;
		reg_cfg_tbl++;
	}

	return rc;
}