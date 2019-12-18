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
typedef  int /*<<< orphan*/  u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int /*<<< orphan*/  OV534_OP_WRITE_3 ; 
 int /*<<< orphan*/  OV534_REG_OPERATION ; 
 int /*<<< orphan*/  OV534_REG_SUBADDR ; 
 int /*<<< orphan*/  OV534_REG_WRITE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  reg_w_i (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_check_status (struct gspca_dev*) ; 

__attribute__((used)) static void sccb_write(struct gspca_dev *gspca_dev, u8 reg, u8 val)
{
	PDEBUG(D_USBO, "sccb_write [%02x] = %02x", reg, val);
	reg_w_i(gspca_dev, OV534_REG_SUBADDR, reg);
	reg_w_i(gspca_dev, OV534_REG_WRITE, val);
	reg_w_i(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_3);

	if (!sccb_check_status(gspca_dev))
		err("sccb_write failed");
}