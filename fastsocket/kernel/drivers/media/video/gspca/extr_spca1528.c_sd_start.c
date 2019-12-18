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
struct sd {scalar_t__ pkt_seq; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcolor (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  sethue (struct gspca_dev*) ; 
 int /*<<< orphan*/  setsharpness (struct gspca_dev*) ; 
 int /*<<< orphan*/  wait_status_0 (struct gspca_dev*) ; 
 int /*<<< orphan*/  wait_status_1 (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* initialize the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->height, gspca_dev->width,
			0x22);		/* JPEG 411 */

	/* the JPEG quality seems to be 82% */
	jpeg_set_qual(sd->jpeg_hdr, 82);

	/* set the controls */
	setbrightness(gspca_dev);
	setcontrast(gspca_dev);
	sethue(gspca_dev);
	setcolor(gspca_dev);
	setsharpness(gspca_dev);

	msleep(5);
	reg_r(gspca_dev, 0x00, 0x2520, 1);
	msleep(8);

	/* start the capture */
	wait_status_0(gspca_dev);
	reg_w(gspca_dev, 0x31, 0x0000, 0x0004);
	wait_status_1(gspca_dev);
	wait_status_0(gspca_dev);
	msleep(200);

	sd->pkt_seq = 0;
	return gspca_dev->usb_err;
}