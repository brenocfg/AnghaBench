#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_se401 {unsigned char sizes; unsigned char* width; unsigned char* height; int maxframesize; unsigned char cwidth; unsigned char cheight; unsigned char brightness; int resetlevel; int rgain; int ggain; int bgain; int enhance; int /*<<< orphan*/ * inturb; TYPE_1__* dev; int /*<<< orphan*/  button; scalar_t__ readcount; scalar_t__ framecount; scalar_t__ error; scalar_t__ dropped; int /*<<< orphan*/  palette; } ;
typedef  int /*<<< orphan*/  cp ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SE401_BUTTON_ENDPOINT ; 
 unsigned char SE401_FORMAT_BAYER ; 
 int /*<<< orphan*/  SE401_REQ_CAMERA_POWER ; 
 int /*<<< orphan*/  SE401_REQ_GET_BRT ; 
 int /*<<< orphan*/  SE401_REQ_GET_CAMERA_DESCRIPTOR ; 
 int /*<<< orphan*/  SE401_REQ_GET_HEIGHT ; 
 int /*<<< orphan*/  SE401_REQ_GET_WIDTH ; 
 int /*<<< orphan*/  SE401_REQ_LED_CONTROL ; 
 int /*<<< orphan*/  SE401_REQ_SET_OUTPUT_MODE ; 
 int /*<<< orphan*/  VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se401_button_irq ; 
 int /*<<< orphan*/  se401_set_exposure (struct usb_se401*,int) ; 
 int se401_sndctrl (int,struct usb_se401*,int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct usb_se401*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int se401_init(struct usb_se401 *se401, int button)
{
	int i = 0, rc;
	unsigned char cp[0x40];
	char temp[200];
	int slen;

	/* led on */
	se401_sndctrl(1, se401, SE401_REQ_LED_CONTROL, 1, NULL, 0);

	/* get camera descriptor */
	rc = se401_sndctrl(0, se401, SE401_REQ_GET_CAMERA_DESCRIPTOR, 0,
							cp, sizeof(cp));
	if (cp[1] != 0x41) {
		err("Wrong descriptor type");
		return 1;
	}
	slen = snprintf(temp, 200, "ExtraFeatures: %d", cp[3]);

	se401->sizes = cp[4] + cp[5] * 256;
	se401->width = kmalloc(se401->sizes*sizeof(int), GFP_KERNEL);
	if (!se401->width)
		return 1;
	se401->height = kmalloc(se401->sizes*sizeof(int), GFP_KERNEL);
	if (!se401->height) {
		kfree(se401->width);
		return 1;
	}
	for (i = 0; i < se401->sizes; i++) {
		se401->width[i] = cp[6 + i * 4 + 0] + cp[6 + i*4 + 1] * 256;
		se401->height[i] = cp[6 + i * 4 + 2] + cp[6 + i * 4 + 3] * 256;
	}
	slen += snprintf(temp + slen, 200 - slen, " Sizes:");
	for (i = 0; i < se401->sizes; i++) {
		slen +=  snprintf(temp + slen, 200 - slen,
			" %dx%d", se401->width[i], se401->height[i]);
	}
	dev_info(&se401->dev->dev, "%s\n", temp);
	se401->maxframesize = se401->width[se401->sizes-1] *
					se401->height[se401->sizes - 1] * 3;

	rc = se401_sndctrl(0, se401, SE401_REQ_GET_WIDTH, 0, cp, sizeof(cp));
	se401->cwidth = cp[0]+cp[1]*256;
	rc = se401_sndctrl(0, se401, SE401_REQ_GET_HEIGHT, 0, cp, sizeof(cp));
	se401->cheight = cp[0]+cp[1]*256;

	if (!(cp[2] & SE401_FORMAT_BAYER)) {
		err("Bayer format not supported!");
		return 1;
	}
	/* set output mode (BAYER) */
	se401_sndctrl(1, se401, SE401_REQ_SET_OUTPUT_MODE,
						SE401_FORMAT_BAYER, NULL, 0);

	rc = se401_sndctrl(0, se401, SE401_REQ_GET_BRT, 0, cp, sizeof(cp));
	se401->brightness = cp[0]+cp[1]*256;
	/* some default values */
	se401->resetlevel = 0x2d;
	se401->rgain = 0x20;
	se401->ggain = 0x20;
	se401->bgain = 0x20;
	se401_set_exposure(se401, 20000);
	se401->palette = VIDEO_PALETTE_RGB24;
	se401->enhance = 1;
	se401->dropped = 0;
	se401->error = 0;
	se401->framecount = 0;
	se401->readcount = 0;

	/* Start interrupt transfers for snapshot button */
	if (button) {
		se401->inturb = usb_alloc_urb(0, GFP_KERNEL);
		if (!se401->inturb) {
			dev_info(&se401->dev->dev,
				 "Allocation of inturb failed\n");
			return 1;
		}
		usb_fill_int_urb(se401->inturb, se401->dev,
		    usb_rcvintpipe(se401->dev, SE401_BUTTON_ENDPOINT),
		    &se401->button, sizeof(se401->button),
		    se401_button_irq,
		    se401,
		    8
		);
		if (usb_submit_urb(se401->inturb, GFP_KERNEL)) {
			dev_info(&se401->dev->dev, "int urb burned down\n");
			return 1;
		}
	} else
		se401->inturb = NULL;

	/* Flash the led */
	se401_sndctrl(1, se401, SE401_REQ_CAMERA_POWER, 1, NULL, 0);
	se401_sndctrl(1, se401, SE401_REQ_LED_CONTROL, 1, NULL, 0);
	se401_sndctrl(1, se401, SE401_REQ_CAMERA_POWER, 0, NULL, 0);
	se401_sndctrl(1, se401, SE401_REQ_LED_CONTROL, 0, NULL, 0);

	return 0;
}