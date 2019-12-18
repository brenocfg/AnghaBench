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
struct usb_device {int dummy; } ;
struct gspca_dev {struct usb_device* dev; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_w (struct usb_device*,int,int,int) ; 

__attribute__((used)) static void spca506_Setsize(struct gspca_dev *gspca_dev, __u16 code,
			    __u16 xmult, __u16 ymult)
{
	struct usb_device *dev = gspca_dev->dev;

	PDEBUG(D_STREAM, "** SetSize **");
	reg_w(dev, 0x04, (0x18 | (code & 0x07)), 0x0000);
	/* Soft snap 0x40 Hard 0x41 */
	reg_w(dev, 0x04, 0x41, 0x0001);
	reg_w(dev, 0x04, 0x00, 0x0002);
	/* reserved */
	reg_w(dev, 0x04, 0x00, 0x0003);

	/* reserved */
	reg_w(dev, 0x04, 0x00, 0x0004);
	/* reserved */
	reg_w(dev, 0x04, 0x01, 0x0005);
	/* reserced */
	reg_w(dev, 0x04, xmult, 0x0006);
	/* reserved */
	reg_w(dev, 0x04, ymult, 0x0007);
	/* compression 1 */
	reg_w(dev, 0x04, 0x00, 0x0008);
	/* T=64 -> 2 */
	reg_w(dev, 0x04, 0x00, 0x0009);
	/* threshold2D */
	reg_w(dev, 0x04, 0x21, 0x000a);
	/* quantization */
	reg_w(dev, 0x04, 0x00, 0x000b);
}