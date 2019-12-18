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
typedef  int /*<<< orphan*/  u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV534_OP_READ_2 ; 
 int /*<<< orphan*/  OV534_OP_WRITE_2 ; 
 int /*<<< orphan*/  OV534_REG_OPERATION ; 
 int /*<<< orphan*/  OV534_REG_READ ; 
 int /*<<< orphan*/  OV534_REG_SUBADDR ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccb_check_status (struct gspca_dev*) ; 

__attribute__((used)) static u8 sccb_read(struct gspca_dev *gspca_dev, u16 reg)
{
	reg_w(gspca_dev, OV534_REG_SUBADDR, reg);
	reg_w(gspca_dev, OV534_REG_OPERATION, OV534_OP_WRITE_2);
	if (!sccb_check_status(gspca_dev))
		err("sccb_read failed 1");

	reg_w(gspca_dev, OV534_REG_OPERATION, OV534_OP_READ_2);
	if (!sccb_check_status(gspca_dev))
		err("sccb_read failed 2");

	return reg_r(gspca_dev, OV534_REG_READ);
}