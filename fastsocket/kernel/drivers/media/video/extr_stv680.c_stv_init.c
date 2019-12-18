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
struct usb_stv {unsigned char SupportedModes; int CIF; int VGA; int QVGA; unsigned char origMode; int VideoMode; unsigned char cwidth; unsigned char cheight; unsigned char origGain; int maxwidth; int maxheight; int vwidth; int vheight; unsigned long rawbufsize; unsigned long maxframesize; int bulk_in_endpointAddr; int brightness; int colour; int contrast; int hue; int depth; int /*<<< orphan*/  palette; scalar_t__ whiteness; scalar_t__ chgbright; scalar_t__ streaming; scalar_t__ readcount; scalar_t__ framecount; scalar_t__ error; scalar_t__ dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 int /*<<< orphan*/  STV_VIDEO_PALETTE ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stv_set_config (struct usb_stv*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stv_set_video_mode (struct usb_stv*) ; 
 int stv_sndctrl (int,struct usb_stv*,int,int,unsigned char*,int) ; 
 int swapRGB ; 
 int swapRGB_on ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stv_init (struct usb_stv *stv680)
{
	int i = 0;
	unsigned char *buffer;
	unsigned long int bufsize;

	buffer = kzalloc (40, GFP_KERNEL);
	if (buffer == NULL) {
		PDEBUG (0, "STV(e): Out of (small buf) memory");
		return -1;
	}
	udelay (100);

	/* set config 1, interface 0, alternate 0 */
	if ((i = stv_set_config (stv680, 1, 0, 0)) < 0) {
		kfree(buffer);
		PDEBUG (0, "STV(e): set config 1,0,0 failed");
		return -1;
	}
	/* ping camera to be sure STV0680 is present */
	if ((i = stv_sndctrl (0, stv680, 0x88, 0x5678, buffer, 0x02)) != 0x02)
		goto error;
	if ((buffer[0] != 0x56) || (buffer[1] != 0x78)) {
		PDEBUG (1, "STV(e): camera ping failed!!");
		goto error;
	}

	/* get camera descriptor */
	if ((i = stv_sndctrl (2, stv680, 0x06, 0x0200, buffer, 0x09)) != 0x09)
		goto error;
	i = stv_sndctrl (2, stv680, 0x06, 0x0200, buffer, 0x22);
	if (!(i >= 0) && (buffer[7] == 0xa0) && (buffer[8] == 0x23)) {
		PDEBUG (1, "STV(e): Could not get descriptor 0200.");
		goto error;
	}
	if ((i = stv_sndctrl (0, stv680, 0x8a, 0, buffer, 0x02)) != 0x02)
		goto error;
	if ((i = stv_sndctrl (0, stv680, 0x8b, 0, buffer, 0x24)) != 0x24)
		goto error;
	if ((i = stv_sndctrl (0, stv680, 0x85, 0, buffer, 0x10)) != 0x10)
		goto error;

	stv680->SupportedModes = buffer[7];
	i = stv680->SupportedModes;
	stv680->CIF = 0;
	stv680->VGA = 0;
	stv680->QVGA = 0;
	if (i & 1)
		stv680->CIF = 1;
	if (i & 2)
		stv680->VGA = 1;
	if (i & 8)
		stv680->QVGA = 1;
	if (stv680->SupportedModes == 0) {
		PDEBUG (0, "STV(e): There are NO supported STV680 modes!!");
		i = -1;
		goto error;
	} else {
		if (stv680->CIF)
			PDEBUG (0, "STV(i): CIF is supported");
		if (stv680->QVGA)
			PDEBUG (0, "STV(i): QVGA is supported");
	}
	/* FW rev, ASIC rev, sensor ID  */
	PDEBUG (1, "STV(i): Firmware rev is %i.%i", buffer[0], buffer[1]);
	PDEBUG (1, "STV(i): ASIC rev is %i.%i", buffer[2], buffer[3]);
	PDEBUG (1, "STV(i): Sensor ID is %i", (buffer[4]*16) + (buffer[5]>>4));

	/*  set alternate interface 1 */
	if ((i = stv_set_config (stv680, 1, 0, 1)) < 0)
		goto error;

	if ((i = stv_sndctrl (0, stv680, 0x85, 0, buffer, 0x10)) != 0x10)
		goto error;
	if ((i = stv_sndctrl (0, stv680, 0x8d, 0, buffer, 0x08)) != 0x08)
		goto error;
	i = buffer[3];
	PDEBUG (0, "STV(i): Camera has %i pictures.", i);

	/*  get current mode */
	if ((i = stv_sndctrl (0, stv680, 0x87, 0, buffer, 0x08)) != 0x08)
		goto error;
	stv680->origMode = buffer[0];	/* 01 = VGA, 03 = QVGA, 00 = CIF */

	/* This will attemp CIF mode, if supported. If not, set to QVGA  */
	memset (buffer, 0, 8);
	if (stv680->CIF)
		buffer[0] = 0x00;
	else if (stv680->QVGA)
		buffer[0] = 0x03;
	if ((i = stv_sndctrl (3, stv680, 0x07, 0x0100, buffer, 0x08)) != 0x08) {
		PDEBUG (0, "STV(i): Set_Camera_Mode failed");
		i = -1;
		goto error;
	}
	buffer[0] = 0xf0;
	stv_sndctrl (0, stv680, 0x87, 0, buffer, 0x08);
	if (((stv680->CIF == 1) && (buffer[0] != 0x00)) || ((stv680->QVGA == 1) && (buffer[0] != 0x03))) {
		PDEBUG (0, "STV(e): Error setting camera video mode!");
		i = -1;
		goto error;
	} else {
		if (buffer[0] == 0) {
			stv680->VideoMode = 0x0000;
			PDEBUG (0, "STV(i): Video Mode set to CIF");
		}
		if (buffer[0] == 0x03) {
			stv680->VideoMode = 0x0300;
			PDEBUG (0, "STV(i): Video Mode set to QVGA");
		}
	}
	if ((i = stv_sndctrl (0, stv680, 0x8f, 0, buffer, 0x10)) != 0x10)
		goto error;
	bufsize = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
	stv680->cwidth = (buffer[4] << 8) | (buffer[5]);	/* ->camera = 322, 356, 644  */
	stv680->cheight = (buffer[6] << 8) | (buffer[7]);	/* ->camera = 242, 292, 484  */
	stv680->origGain = buffer[12];

	goto exit;

error:
	i = stv_sndctrl (0, stv680, 0x80, 0, buffer, 0x02);	/* Get Last Error */
	PDEBUG (1, "STV(i): last error: %i,  command = 0x%x", buffer[0], buffer[1]);
	kfree(buffer);
	return -1;

exit:
	kfree(buffer);

	/* video = 320x240, 352x288 */
	if (stv680->CIF == 1) {
		stv680->maxwidth = 352;
		stv680->maxheight = 288;
		stv680->vwidth = 352;
		stv680->vheight = 288;
	}
	if (stv680->QVGA == 1) {
		stv680->maxwidth = 320;
		stv680->maxheight = 240;
		stv680->vwidth = 320;
		stv680->vheight = 240;
	}

	stv680->rawbufsize = bufsize;	/* must be ./. by 8 */
	stv680->maxframesize = bufsize * 3;	/* RGB size */
	PDEBUG (2, "STV(i): cwidth = %i, cheight = %i", stv680->cwidth, stv680->cheight);
	PDEBUG (1, "STV(i): width = %i, height = %i, rawbufsize = %li", stv680->vwidth, stv680->vheight, stv680->rawbufsize);

	/* some default values */
	stv680->bulk_in_endpointAddr = 0x82;
	stv680->dropped = 0;
	stv680->error = 0;
	stv680->framecount = 0;
	stv680->readcount = 0;
	stv680->streaming = 0;
	/* bright, white, colour, hue, contrast are set by software, not in stv0680 */
	stv680->brightness = 32767;
	stv680->chgbright = 0;
	stv680->whiteness = 0;	/* only for greyscale */
	stv680->colour = 32767;
	stv680->contrast = 32767;
	stv680->hue = 32767;
	stv680->palette = STV_VIDEO_PALETTE;
	stv680->depth = 24;	/* rgb24 bits */
	if ((swapRGB_on == 0) && (swapRGB == 0))
		PDEBUG (1, "STV(i): swapRGB is (auto) OFF");
	else if ((swapRGB_on == 0) && (swapRGB == 1))
		PDEBUG (1, "STV(i): swapRGB is (auto) ON");
	else if (swapRGB_on == 1)
		PDEBUG (1, "STV(i): swapRGB is (forced) ON");
	else if (swapRGB_on == -1)
		PDEBUG (1, "STV(i): swapRGB is (forced) OFF");

	if (stv_set_video_mode (stv680) < 0) {
		PDEBUG (0, "STV(e): Could not set video mode in stv_init");
		return -1;
	}

	return 0;
}