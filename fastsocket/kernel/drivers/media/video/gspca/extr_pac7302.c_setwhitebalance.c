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
struct sd {int white_balance; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int D_CONF ; 
 int D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setwhitebalance(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w(gspca_dev, 0xff, 0x00);		/* page 0 */
	reg_w(gspca_dev, 0xc6, sd->white_balance);

	reg_w(gspca_dev, 0xdc, 0x01);
	PDEBUG(D_CONF|D_STREAM, "white_balance: %i", sd->white_balance);
}