#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_device {int dummy; } ;
struct sd {scalar_t__ subtype; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_2__ cam; struct usb_device* dev; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int D_CONF ; 
 int D_ERR ; 
 scalar_t__ Nxultra ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
 int SPCA50X_CUSB_ENABLE ; 
 int SPCA50X_REG_COMPRESS ; 
 int SPCA50X_REG_USB ; 
 int SPCA50X_USB_CTRL ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int reg_read (struct gspca_dev*,int,int) ; 
 int reg_write (struct usb_device*,int,int,int) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca505_open_data_ccd ; 
 int /*<<< orphan*/  spca505b_open_data_ccd ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct usb_device *dev = gspca_dev->dev;
	int ret, mode;
	static u8 mode_tb[][3] = {
	/*	  r00   r06   r07	*/
		{0x00, 0x10, 0x10},	/* 640x480 */
		{0x01, 0x1a, 0x1a},	/* 352x288 */
		{0x02, 0x1c, 0x1d},	/* 320x240 */
		{0x04, 0x34, 0x34},	/* 176x144 */
		{0x05, 0x40, 0x40}	/* 160x120 */
	};

	if (sd->subtype == Nxultra)
		write_vector(gspca_dev, spca505b_open_data_ccd);
	else
		write_vector(gspca_dev, spca505_open_data_ccd);
	ret = reg_read(gspca_dev, 0x06, 0x16);

	if (ret < 0) {
		PDEBUG(D_ERR|D_CONF,
		       "register read failed err: %d",
		       ret);
		return ret;
	}
	if (ret != 0x0101) {
		err("After vector read returns 0x%04x should be 0x0101",
			ret);
	}

	ret = reg_write(gspca_dev->dev, 0x06, 0x16, 0x0a);
	if (ret < 0)
		return ret;
	reg_write(gspca_dev->dev, 0x05, 0xc2, 0x12);

	/* necessary because without it we can see stream
	 * only once after loading module */
	/* stopping usb registers Tomasz change */
	reg_write(dev, 0x02, 0x00, 0x00);

	mode = gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv;
	reg_write(dev, SPCA50X_REG_COMPRESS, 0x00, mode_tb[mode][0]);
	reg_write(dev, SPCA50X_REG_COMPRESS, 0x06, mode_tb[mode][1]);
	reg_write(dev, SPCA50X_REG_COMPRESS, 0x07, mode_tb[mode][2]);

	ret = reg_write(dev, SPCA50X_REG_USB,
			 SPCA50X_USB_CTRL,
			 SPCA50X_CUSB_ENABLE);

	setbrightness(gspca_dev);

	return ret;
}