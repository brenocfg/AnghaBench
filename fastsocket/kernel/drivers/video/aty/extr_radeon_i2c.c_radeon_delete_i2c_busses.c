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
struct radeonfb_info {TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rinfo; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void radeon_delete_i2c_busses(struct radeonfb_info *rinfo)
{
	if (rinfo->i2c[0].rinfo)
		i2c_del_adapter(&rinfo->i2c[0].adapter);
	rinfo->i2c[0].rinfo = NULL;

	if (rinfo->i2c[1].rinfo)
		i2c_del_adapter(&rinfo->i2c[1].adapter);
	rinfo->i2c[1].rinfo = NULL;

	if (rinfo->i2c[2].rinfo)
		i2c_del_adapter(&rinfo->i2c[2].adapter);
	rinfo->i2c[2].rinfo = NULL;

	if (rinfo->i2c[3].rinfo)
		i2c_del_adapter(&rinfo->i2c[3].adapter);
	rinfo->i2c[3].rinfo = NULL;
}