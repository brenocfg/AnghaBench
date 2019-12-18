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
struct TYPE_2__ {int /*<<< orphan*/  usb_err; } ;
struct sd {TYPE_1__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int w9968cf_read_sb (struct sd*) ; 
 int /*<<< orphan*/  w9968cf_write_sb (struct sd*,int) ; 

__attribute__((used)) static void w9968cf_smbus_read_ack(struct sd *sd)
{
	int sda;

	/* Ensure SDA is high before raising clock to avoid a spurious stop */
	w9968cf_write_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
	w9968cf_write_sb(sd, 0x0013); /* SDE=1, SDA=1, SCL=1 */
	sda = w9968cf_read_sb(sd);
	w9968cf_write_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
	if (sda >= 0 && (sda & 0x08)) {
		PDEBUG(D_USBI, "Did not receive i2c ACK");
		sd->gspca_dev.usb_err = -EIO;
	}
}