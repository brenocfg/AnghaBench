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
 scalar_t__ CC_OV6620 ; 
 void* CC_OV6630 ; 
 int /*<<< orphan*/  GENERIC_REG_COM_I ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  PERROR (char*) ; 
 int /*<<< orphan*/  PINFO (char*) ; 
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ov6x20_ops ; 
 int /*<<< orphan*/  ov6x30_ops ; 
 int ov_read (struct i2c_client*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov6xx0_detect(struct i2c_client *c)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	int rc;
	unsigned char val;

	PDEBUG(4, "");

	/* Detect chip (sub)type */
	rc = ov_read(c, GENERIC_REG_COM_I, &val);
	if (rc < 0) {
		PERROR("Error detecting ov6xx0 type");
		return -1;
	}

	if ((val & 3) == 0) {
		ov->subtype = CC_OV6630;
		PINFO("Camera chip is an OV6630");
	} else if ((val & 3) == 1) {
		ov->subtype = CC_OV6620;
		PINFO("Camera chip is an OV6620");
	} else if ((val & 3) == 2) {
		ov->subtype = CC_OV6630;
		PINFO("Camera chip is an OV6630AE");
	} else if ((val & 3) == 3) {
		ov->subtype = CC_OV6630;
		PINFO("Camera chip is an OV6630AF");
	}

	if (ov->subtype == CC_OV6620)
		ov->sops = &ov6x20_ops;
	else
		ov->sops = &ov6x30_ops;

	return 0;
}