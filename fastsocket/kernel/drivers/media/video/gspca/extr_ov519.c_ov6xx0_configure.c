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
struct sd {int sif; void* sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  OV7610_REG_COM_I ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 void* SEN_OV6620 ; 
 void* SEN_OV6630 ; 
 void* SEN_OV66308AF ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int i2c_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void ov6xx0_configure(struct sd *sd)
{
	int rc;
	PDEBUG(D_PROBE, "starting OV6xx0 configuration");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);
	if (rc < 0) {
		PDEBUG(D_ERR, "Error detecting sensor type");
		return;
	}

	/* Ugh. The first two bits are the version bits, but
	 * the entire register value must be used. I guess OVT
	 * underestimated how many variants they would make. */
	switch (rc) {
	case 0x00:
		sd->sensor = SEN_OV6630;
		warn("WARNING: Sensor is an OV66308. Your camera may have");
		warn("been misdetected in previous driver versions.");
		break;
	case 0x01:
		sd->sensor = SEN_OV6620;
		PDEBUG(D_PROBE, "Sensor is an OV6620");
		break;
	case 0x02:
		sd->sensor = SEN_OV6630;
		PDEBUG(D_PROBE, "Sensor is an OV66308AE");
		break;
	case 0x03:
		sd->sensor = SEN_OV66308AF;
		PDEBUG(D_PROBE, "Sensor is an OV66308AF");
		break;
	case 0x90:
		sd->sensor = SEN_OV6630;
		warn("WARNING: Sensor is an OV66307. Your camera may have");
		warn("been misdetected in previous driver versions.");
		break;
	default:
		err("FATAL: Unknown sensor version: 0x%02x", rc);
		return;
	}

	/* Set sensor-specific vars */
	sd->sif = 1;
}