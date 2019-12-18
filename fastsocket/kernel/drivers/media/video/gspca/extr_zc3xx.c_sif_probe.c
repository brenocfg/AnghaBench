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
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SENSOR_PAS106 ; 
 int i2c_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  send_unknown (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_2wr_probe (struct gspca_dev*,int) ; 

__attribute__((used)) static int sif_probe(struct gspca_dev *gspca_dev)
{
	u16 checkword;

	start_2wr_probe(gspca_dev, 0x0f);		/* PAS106 */
	reg_w(gspca_dev, 0x08, 0x008d);
	msleep(150);
	checkword = ((i2c_read(gspca_dev, 0x00) & 0x0f) << 4)
			| ((i2c_read(gspca_dev, 0x01) & 0xf0) >> 4);
	PDEBUG(D_PROBE, "probe sif 0x%04x", checkword);
	if (checkword == 0x0007) {
		send_unknown(gspca_dev, SENSOR_PAS106);
		return 0x0f;			/* PAS106 */
	}
	return -1;
}