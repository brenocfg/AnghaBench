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
struct sd {int contrast; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  RGBG ;

/* Variables and functions */
 int /*<<< orphan*/  ET_G_RED ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 RGBG[] = { 0x80, 0x80, 0x80, 0x80, 0x00, 0x00 };
	__u8 contrast = sd->contrast;

	memset(RGBG, contrast, sizeof(RGBG) - 2);
	reg_w(gspca_dev, ET_G_RED, RGBG, 6);
}