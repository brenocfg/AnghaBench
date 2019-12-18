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
struct sd {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  OV7610_REG_COM_I ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SEN_OV8610 ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int i2c_r (struct sd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov8xx0_configure(struct sd *sd)
{
	int rc;

	PDEBUG(D_PROBE, "starting ov8xx0 configuration");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);
	if (rc < 0) {
		PDEBUG(D_ERR, "Error detecting sensor type");
		return;
	}
	if ((rc & 3) == 1)
		sd->sensor = SEN_OV8610;
	else
		err("Unknown image sensor version: %d", rc & 3);
}