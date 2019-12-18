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
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r_12 (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spca504_acknowledged_command(struct gspca_dev *gspca_dev,
			     u8 req, u16 idx, u16 val)
{
	u16 notdone;

	reg_w_riv(gspca_dev, req, idx, val);
	notdone = reg_r_12(gspca_dev, 0x01, 0x0001, 1);
	reg_w_riv(gspca_dev, req, idx, val);

	PDEBUG(D_FRAM, "before wait 0x%04x", notdone);

	msleep(200);
	notdone = reg_r_12(gspca_dev, 0x01, 0x0001, 1);
	PDEBUG(D_FRAM, "after wait 0x%04x", notdone);
}