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
struct ovcamchip_regvals {int reg; int /*<<< orphan*/  val; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ov_write (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

int ov_write_regvals(struct i2c_client *c, struct ovcamchip_regvals *rvals)
{
	int rc;

	while (rvals->reg != 0xff) {
		rc = ov_write(c, rvals->reg, rvals->val);
		if (rc < 0)
			return rc;
		rvals++;
	}

	return 0;
}