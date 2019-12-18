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
struct i2o_controller {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int i2o_iop_enable (struct i2o_controller*) ; 
 int i2o_iop_systab_set (struct i2o_controller*) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2o_iop_online(struct i2o_controller *c)
{
	int rc;

	rc = i2o_iop_systab_set(c);
	if (rc)
		return rc;

	/* In READY state */
	osm_debug("%s: Attempting to enable...\n", c->name);
	rc = i2o_iop_enable(c);
	if (rc)
		return rc;

	return 0;
}