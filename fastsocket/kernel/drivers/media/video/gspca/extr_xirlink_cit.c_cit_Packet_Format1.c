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
 int /*<<< orphan*/  cit_read_reg (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cit_send_00_04_06 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_send_FF_04_02 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_send_x_00 (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  cit_send_x_00_05 (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  cit_send_x_00_05_02_01 (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  cit_send_x_00_05_02_08_01 (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  cit_send_x_01_00_05 (struct gspca_dev*,int) ; 

__attribute__((used)) static void cit_Packet_Format1(struct gspca_dev *gspca_dev, u16 fkey, u16 val)
{
	cit_send_x_01_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05(gspca_dev, fkey);
	cit_send_x_00_05_02_08_01(gspca_dev, val);
	cit_send_x_00_05(gspca_dev, 0x0088);
	cit_send_x_00_05_02_01(gspca_dev, fkey);
	cit_send_x_00_05(gspca_dev, 0x0089);
	cit_send_x_00(gspca_dev, fkey);
	cit_send_00_04_06(gspca_dev);
	cit_read_reg(gspca_dev, 0x0126, 0);
	cit_send_FF_04_02(gspca_dev);
}