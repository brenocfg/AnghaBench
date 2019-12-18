#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uvd {int debug; int iface; int ifaceAltInactive; int ifaceAltActive; unsigned char video_endp; int iso_packet_len; long paletteBits; long defaultPalette; int /*<<< orphan*/  videosize; int /*<<< orphan*/  canvas; struct usb_device* dev; int /*<<< orphan*/  flags; } ;
struct usb_interface {int num_altsetting; struct usb_host_interface* altsetting; } ;
struct TYPE_6__ {int bInterfaceNumber; int bAlternateSetting; int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct usb_endpoint_descriptor {unsigned char bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {int bNumConfigurations; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
typedef  int __u8 ;
struct TYPE_8__ {int camera_model; scalar_t__ initialized; } ;
struct TYPE_7__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
#define  IBMCAM_MODEL_1 141 
#define  IBMCAM_MODEL_2 140 
#define  IBMCAM_MODEL_3 139 
#define  IBMCAM_MODEL_4 138 
#define  IBMCAM_PRODUCT_ID 137 
 TYPE_4__* IBMCAM_T (struct uvd*) ; 
#define  NETCAM_PRODUCT_ID 136 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int,int) ; 
#define  SIZE_128x96 135 
#define  SIZE_160x120 134 
#define  SIZE_176x144 133 
#define  SIZE_320x240 132 
 int SIZE_352x240 ; 
#define  SIZE_352x288 131 
#define  SIZE_640x480 130 
#define  VEO_800C_PRODUCT_ID 129 
#define  VEO_800D_PRODUCT_ID 128 
 int /*<<< orphan*/  VIDEOSIZE (int,int) ; 
 long VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cams ; 
 int debug ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  flags ; 
 int framerate ; 
 int /*<<< orphan*/  ibmcam_configure_video (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_size_to_videosize (int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int lighting ; 
 int size ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct uvd*) ; 
 struct uvd* usbvideo_AllocateDevice (int /*<<< orphan*/ ) ; 
 int usbvideo_RegisterVideoDevice (struct uvd*) ; 

__attribute__((used)) static int ibmcam_probe(struct usb_interface *intf, const struct usb_device_id *devid)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct uvd *uvd = NULL;
	int ix, i, nas, model=0, canvasX=0, canvasY=0;
	int actInterface=-1, inactInterface=-1, maxPS=0;
	__u8 ifnum = intf->altsetting->desc.bInterfaceNumber;
	unsigned char video_ep = 0;

	if (debug >= 1)
		dev_info(&dev->dev, "ibmcam_probe(%p,%u.)\n", intf, ifnum);

	/* We don't handle multi-config cameras */
	if (dev->descriptor.bNumConfigurations != 1)
		return -ENODEV;

	/* Check the version/revision */
	switch (le16_to_cpu(dev->descriptor.bcdDevice)) {
	case 0x0002:
		if (ifnum != 2)
			return -ENODEV;
		model = IBMCAM_MODEL_1;
		break;
	case 0x030A:
		if (ifnum != 0)
			return -ENODEV;
		if ((le16_to_cpu(dev->descriptor.idProduct) == NETCAM_PRODUCT_ID) ||
		    (le16_to_cpu(dev->descriptor.idProduct) == VEO_800D_PRODUCT_ID))
			model = IBMCAM_MODEL_4;
		else
			model = IBMCAM_MODEL_2;
		break;
	case 0x0301:
		if (ifnum != 0)
			return -ENODEV;
		model = IBMCAM_MODEL_3;
		break;
	default:
		err("IBM camera with revision 0x%04x is not supported.",
			le16_to_cpu(dev->descriptor.bcdDevice));
		return -ENODEV;
	}

	/* Print detailed info on what we found so far */
	do {
		char *brand = NULL;
		switch (le16_to_cpu(dev->descriptor.idProduct)) {
		case NETCAM_PRODUCT_ID:
			brand = "IBM NetCamera";
			break;
		case VEO_800C_PRODUCT_ID:
			brand = "Veo Stingray [800C]";
			break;
		case VEO_800D_PRODUCT_ID:
			brand = "Veo Stingray [800D]";
			break;
		case IBMCAM_PRODUCT_ID:
		default:
			brand = "IBM PC Camera"; /* a.k.a. Xirlink C-It */
			break;
		}
		dev_info(&dev->dev,
			 "%s USB camera found (model %d, rev. 0x%04x)\n",
			 brand, model, le16_to_cpu(dev->descriptor.bcdDevice));
	} while (0);

	/* Validate found interface: must have one ISO endpoint */
	nas = intf->num_altsetting;
	if (debug > 0)
		dev_info(&dev->dev, "Number of alternate settings=%d.\n",
			 nas);
	if (nas < 2) {
		err("Too few alternate settings for this camera!");
		return -ENODEV;
	}
	/* Validate all alternate settings */
	for (ix=0; ix < nas; ix++) {
		const struct usb_host_interface *interface;
		const struct usb_endpoint_descriptor *endpoint;

		interface = &intf->altsetting[ix];
		i = interface->desc.bAlternateSetting;
		if (interface->desc.bNumEndpoints != 1) {
			err("Interface %d. has %u. endpoints!",
			    ifnum, (unsigned)(interface->desc.bNumEndpoints));
			return -ENODEV;
		}
		endpoint = &interface->endpoint[0].desc;
		if (video_ep == 0)
			video_ep = endpoint->bEndpointAddress;
		else if (video_ep != endpoint->bEndpointAddress) {
			err("Alternate settings have different endpoint addresses!");
			return -ENODEV;
		}
		if (!usb_endpoint_xfer_isoc(endpoint)) {
			err("Interface %d. has non-ISO endpoint!", ifnum);
			return -ENODEV;
		}
		if (usb_endpoint_dir_out(endpoint)) {
			err("Interface %d. has ISO OUT endpoint!", ifnum);
			return -ENODEV;
		}
		if (le16_to_cpu(endpoint->wMaxPacketSize) == 0) {
			if (inactInterface < 0)
				inactInterface = i;
			else {
				err("More than one inactive alt. setting!");
				return -ENODEV;
			}
		} else {
			if (actInterface < 0) {
				actInterface = i;
				maxPS = le16_to_cpu(endpoint->wMaxPacketSize);
				if (debug > 0)
					dev_info(&dev->dev,
						 "Active setting=%d. "
						 "maxPS=%d.\n", i, maxPS);
			} else
				err("More than one active alt. setting! Ignoring #%d.", i);
		}
	}
	if ((maxPS <= 0) || (actInterface < 0) || (inactInterface < 0)) {
		err("Failed to recognize the camera!");
		return -ENODEV;
	}

	/* Validate options */
	switch (model) {
	case IBMCAM_MODEL_1:
		RESTRICT_TO_RANGE(lighting, 0, 2);
		RESTRICT_TO_RANGE(size, SIZE_128x96, SIZE_352x288);
		if (framerate < 0)
			framerate = 2;
		canvasX = 352;
		canvasY = 288;
		break;
	case IBMCAM_MODEL_2:
		RESTRICT_TO_RANGE(lighting, 0, 15);
		RESTRICT_TO_RANGE(size, SIZE_176x144, SIZE_352x240);
		if (framerate < 0)
			framerate = 2;
		canvasX = 352;
		canvasY = 240;
		break;
	case IBMCAM_MODEL_3:
		RESTRICT_TO_RANGE(lighting, 0, 15); /* FIXME */
		switch (size) {
		case SIZE_160x120:
			canvasX = 160;
			canvasY = 120;
			if (framerate < 0)
				framerate = 2;
			RESTRICT_TO_RANGE(framerate, 0, 5);
			break;
		default:
			dev_info(&dev->dev, "IBM camera: using 320x240\n");
			size = SIZE_320x240;
			/* No break here */
		case SIZE_320x240:
			canvasX = 320;
			canvasY = 240;
			if (framerate < 0)
				framerate = 3;
			RESTRICT_TO_RANGE(framerate, 0, 5);
			break;
		case SIZE_640x480:
			canvasX = 640;
			canvasY = 480;
			framerate = 0;	/* Slowest, and maybe even that is too fast */
			break;
		}
		break;
	case IBMCAM_MODEL_4:
		RESTRICT_TO_RANGE(lighting, 0, 2);
		switch (size) {
		case SIZE_128x96:
			canvasX = 128;
			canvasY = 96;
			break;
		case SIZE_160x120:
			canvasX = 160;
			canvasY = 120;
			break;
		default:
			dev_info(&dev->dev, "IBM NetCamera: using 176x144\n");
			size = SIZE_176x144;
			/* No break here */
		case SIZE_176x144:
			canvasX = 176;
			canvasY = 144;
			break;
		case SIZE_320x240:
			canvasX = 320;
			canvasY = 240;
			break;
		case SIZE_352x288:
			canvasX = 352;
			canvasY = 288;
			break;
		}
		break;
	default:
		err("IBM camera: Model %d. not supported!", model);
		return -ENODEV;
	}

	uvd = usbvideo_AllocateDevice(cams);
	if (uvd != NULL) {
		/* Here uvd is a fully allocated uvd object */
		uvd->flags = flags;
		uvd->debug = debug;
		uvd->dev = dev;
		uvd->iface = ifnum;
		uvd->ifaceAltInactive = inactInterface;
		uvd->ifaceAltActive = actInterface;
		uvd->video_endp = video_ep;
		uvd->iso_packet_len = maxPS;
		uvd->paletteBits = 1L << VIDEO_PALETTE_RGB24;
		uvd->defaultPalette = VIDEO_PALETTE_RGB24;
		uvd->canvas = VIDEOSIZE(canvasX, canvasY);
		uvd->videosize = ibmcam_size_to_videosize(size);

		/* Initialize ibmcam-specific data */
		assert(IBMCAM_T(uvd) != NULL);
		IBMCAM_T(uvd)->camera_model = model;
		IBMCAM_T(uvd)->initialized = 0;

		ibmcam_configure_video(uvd);

		i = usbvideo_RegisterVideoDevice(uvd);
		if (i != 0) {
			err("usbvideo_RegisterVideoDevice() failed.");
			uvd = NULL;
		}
	}
	usb_set_intfdata (intf, uvd);
	return 0;
}