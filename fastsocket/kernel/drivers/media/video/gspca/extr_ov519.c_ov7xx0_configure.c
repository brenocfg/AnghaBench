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
struct sd {void* sensor; int /*<<< orphan*/  invert_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_PROBE ; 
 int OV7610_REG_COM_I ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 void* SEN_OV7610 ; 
 void* SEN_OV7620 ; 
 void* SEN_OV7620AE ; 
 void* SEN_OV7640 ; 
 void* SEN_OV7648 ; 
 void* SEN_OV7660 ; 
 void* SEN_OV7670 ; 
 void* SEN_OV76BE ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int i2c_r (struct sd*,int) ; 

__attribute__((used)) static void ov7xx0_configure(struct sd *sd)
{
	int rc, high, low;

	PDEBUG(D_PROBE, "starting OV7xx0 configuration");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);

	/* add OV7670 here
	 * it appears to be wrongly detected as a 7610 by default */
	if (rc < 0) {
		PDEBUG(D_ERR, "Error detecting sensor type");
		return;
	}
	if ((rc & 3) == 3) {
		/* quick hack to make OV7670s work */
		high = i2c_r(sd, 0x0a);
		low = i2c_r(sd, 0x0b);
		/* info("%x, %x", high, low); */
		if (high == 0x76 && (low & 0xf0) == 0x70) {
			PDEBUG(D_PROBE, "Sensor is an OV76%02x", low);
			sd->sensor = SEN_OV7670;
		} else {
			PDEBUG(D_PROBE, "Sensor is an OV7610");
			sd->sensor = SEN_OV7610;
		}
	} else if ((rc & 3) == 1) {
		/* I don't know what's different about the 76BE yet. */
		if (i2c_r(sd, 0x15) & 1) {
			PDEBUG(D_PROBE, "Sensor is an OV7620AE");
			sd->sensor = SEN_OV7620AE;
		} else {
			PDEBUG(D_PROBE, "Sensor is an OV76BE");
			sd->sensor = SEN_OV76BE;
		}
	} else if ((rc & 3) == 0) {
		/* try to read product id registers */
		high = i2c_r(sd, 0x0a);
		if (high < 0) {
			PDEBUG(D_ERR, "Error detecting camera chip PID");
			return;
		}
		low = i2c_r(sd, 0x0b);
		if (low < 0) {
			PDEBUG(D_ERR, "Error detecting camera chip VER");
			return;
		}
		if (high == 0x76) {
			switch (low) {
			case 0x30:
				err("Sensor is an OV7630/OV7635");
				err("7630 is not supported by this driver");
				return;
			case 0x40:
				PDEBUG(D_PROBE, "Sensor is an OV7645");
				sd->sensor = SEN_OV7640; /* FIXME */
				break;
			case 0x45:
				PDEBUG(D_PROBE, "Sensor is an OV7645B");
				sd->sensor = SEN_OV7640; /* FIXME */
				break;
			case 0x48:
				PDEBUG(D_PROBE, "Sensor is an OV7648");
				sd->sensor = SEN_OV7648;
				break;
			case 0x60:
				PDEBUG(D_PROBE, "Sensor is a OV7660");
				sd->sensor = SEN_OV7660;
				sd->invert_led = 0;
				break;
			default:
				PDEBUG(D_PROBE, "Unknown sensor: 0x76%x", low);
				return;
			}
		} else {
			PDEBUG(D_PROBE, "Sensor is an OV7620");
			sd->sensor = SEN_OV7620;
		}
	} else {
		err("Unknown image sensor version: %d", rc & 3);
	}
}