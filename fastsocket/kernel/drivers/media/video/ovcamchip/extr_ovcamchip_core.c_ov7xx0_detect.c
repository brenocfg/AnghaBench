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
struct ovcamchip {scalar_t__ subtype; int /*<<< orphan*/ * sops; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC_OV7610 ; 
 scalar_t__ CC_OV7620 ; 
 scalar_t__ CC_OV76BE ; 
 int ENOSYS ; 
 int GENERIC_REG_COM_I ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  PERROR (char*,...) ; 
 int /*<<< orphan*/  PINFO (char*) ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ov76be_ops ; 
 int /*<<< orphan*/  ov7x10_ops ; 
 int /*<<< orphan*/  ov7x20_ops ; 
 int ov_read (struct i2c_client*,int,unsigned char*) ; 

__attribute__((used)) static int ov7xx0_detect(struct i2c_client *c)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	int rc;
	unsigned char val;

	PDEBUG(4, "");

	/* Detect chip (sub)type */
	rc = ov_read(c, GENERIC_REG_COM_I, &val);
	if (rc < 0) {
		PERROR("Error detecting ov7xx0 type");
		return rc;
	}

	if ((val & 3) == 3) {
		PINFO("Camera chip is an OV7610");
		ov->subtype = CC_OV7610;
	} else if ((val & 3) == 1) {
		rc = ov_read(c, 0x15, &val);
		if (rc < 0) {
			PERROR("Error detecting ov7xx0 type");
			return rc;
		}

		if (val & 1) {
			PINFO("Camera chip is an OV7620AE");
			/* OV7620 is a close enough match for now. There are
			 * some definite differences though, so this should be
			 * fixed */
			ov->subtype = CC_OV7620;
		} else {
			PINFO("Camera chip is an OV76BE");
			ov->subtype = CC_OV76BE;
		}
	} else if ((val & 3) == 0) {
		PINFO("Camera chip is an OV7620");
		ov->subtype = CC_OV7620;
	} else {
		PERROR("Unknown camera chip version: %d", val & 3);
		return -ENOSYS;
	}

	if (ov->subtype == CC_OV76BE)
		ov->sops = &ov76be_ops;
	else if (ov->subtype == CC_OV7620)
		ov->sops = &ov7x20_ops;
	else
		ov->sops = &ov7x10_ops;

	return 0;
}