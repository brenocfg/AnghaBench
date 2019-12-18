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
struct uvd {int ifaceAltInactive; int ifaceAltActive; unsigned char video_endp; int iso_packet_len; long paletteBits; long defaultPalette; int max_frame_size; void* videosize; void* canvas; int /*<<< orphan*/  iface; struct usb_device* dev; int /*<<< orphan*/  debug; scalar_t__ flags; scalar_t__ user_data; } ;
struct usb_interface {int num_altsetting; struct usb_host_interface* altsetting; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int bAlternateSetting; int bNumEndpoints; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_3__ desc; TYPE_2__* endpoint; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {int bNumConfigurations; int /*<<< orphan*/  bcdDevice; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct konicawc {size_t speed; int width; int height; size_t size; int /*<<< orphan*/ ** sts_urb; } ;
struct TYPE_8__ {int width; int height; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRAMES_PER_DESC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_SPEED ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_160X120 ; 
 int /*<<< orphan*/  SIZE_320X240 ; 
 int USBVIDEO_NUMSBUF ; 
 void* VIDEOSIZE (int,int) ; 
 long VIDEO_PALETTE_YUV420P ; 
 TYPE_4__* camera_sizes ; 
 int /*<<< orphan*/  cams ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  konicawc_configure_video (struct uvd*) ; 
 int /*<<< orphan*/  konicawc_register_input (struct konicawc*,struct usb_device*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t size ; 
 int* spd_to_iface ; 
 size_t speed ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct uvd*) ; 
 struct uvd* usbvideo_AllocateDevice (int /*<<< orphan*/ ) ; 
 int usbvideo_RegisterVideoDevice (struct uvd*) ; 

__attribute__((used)) static int konicawc_probe(struct usb_interface *intf, const struct usb_device_id *devid)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct uvd *uvd = NULL;
	int ix, i, nas;
	int actInterface=-1, inactInterface=-1, maxPS=0;
	unsigned char video_ep = 0;

	DEBUG(1, "konicawc_probe(%p)", intf);

	/* We don't handle multi-config cameras */
	if (dev->descriptor.bNumConfigurations != 1)
		return -ENODEV;

	dev_info(&intf->dev, "Konica Webcam (rev. 0x%04x)\n",
		 le16_to_cpu(dev->descriptor.bcdDevice));
	RESTRICT_TO_RANGE(speed, 0, MAX_SPEED);

	/* Validate found interface: must have one ISO endpoint */
	nas = intf->num_altsetting;
	if (nas != 8) {
		err("Incorrect number of alternate settings (%d) for this camera!", nas);
		return -ENODEV;
	}
	/* Validate all alternate settings */
	for (ix=0; ix < nas; ix++) {
		const struct usb_host_interface *interface;
		const struct usb_endpoint_descriptor *endpoint;

		interface = &intf->altsetting[ix];
		i = interface->desc.bAlternateSetting;
		if (interface->desc.bNumEndpoints != 2) {
			err("Interface %d. has %u. endpoints!",
			    interface->desc.bInterfaceNumber,
			    (unsigned)(interface->desc.bNumEndpoints));
			return -ENODEV;
		}
		endpoint = &interface->endpoint[1].desc;
		DEBUG(1, "found endpoint: addr: 0x%2.2x maxps = 0x%4.4x",
		    endpoint->bEndpointAddress, le16_to_cpu(endpoint->wMaxPacketSize));
		if (video_ep == 0)
			video_ep = endpoint->bEndpointAddress;
		else if (video_ep != endpoint->bEndpointAddress) {
			err("Alternate settings have different endpoint addresses!");
			return -ENODEV;
		}
		if (!usb_endpoint_xfer_isoc(endpoint)) {
			err("Interface %d. has non-ISO endpoint!",
			    interface->desc.bInterfaceNumber);
			return -ENODEV;
		}
		if (usb_endpoint_dir_out(endpoint)) {
			err("Interface %d. has ISO OUT endpoint!",
			    interface->desc.bInterfaceNumber);
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
			if (i == spd_to_iface[speed]) {
				/* This one is the requested one */
				actInterface = i;
			}
		}
		if (le16_to_cpu(endpoint->wMaxPacketSize) > maxPS)
			maxPS = le16_to_cpu(endpoint->wMaxPacketSize);
	}
	if(actInterface == -1) {
		err("Cant find required endpoint");
		return -ENODEV;
	}

	DEBUG(1, "Selecting requested active setting=%d. maxPS=%d.", actInterface, maxPS);

	uvd = usbvideo_AllocateDevice(cams);
	if (uvd != NULL) {
		struct konicawc *cam = (struct konicawc *)(uvd->user_data);
		/* Here uvd is a fully allocated uvd object */
		for(i = 0; i < USBVIDEO_NUMSBUF; i++) {
			cam->sts_urb[i] = usb_alloc_urb(FRAMES_PER_DESC, GFP_KERNEL);
			if(cam->sts_urb[i] == NULL) {
				while(i--) {
					usb_free_urb(cam->sts_urb[i]);
				}
				err("can't allocate urbs");
				return -ENOMEM;
			}
		}
		cam->speed = speed;
		RESTRICT_TO_RANGE(size, SIZE_160X120, SIZE_320X240);
		cam->width = camera_sizes[size].width;
		cam->height = camera_sizes[size].height;
		cam->size = size;

		uvd->flags = 0;
		uvd->debug = debug;
		uvd->dev = dev;
		uvd->iface = intf->altsetting->desc.bInterfaceNumber;
		uvd->ifaceAltInactive = inactInterface;
		uvd->ifaceAltActive = actInterface;
		uvd->video_endp = video_ep;
		uvd->iso_packet_len = maxPS;
		uvd->paletteBits = 1L << VIDEO_PALETTE_YUV420P;
		uvd->defaultPalette = VIDEO_PALETTE_YUV420P;
		uvd->canvas = VIDEOSIZE(320, 240);
		uvd->videosize = VIDEOSIZE(cam->width, cam->height);

		/* Initialize konicawc specific data */
		konicawc_configure_video(uvd);

		i = usbvideo_RegisterVideoDevice(uvd);
		uvd->max_frame_size = (320 * 240 * 3)/2;
		if (i != 0) {
			err("usbvideo_RegisterVideoDevice() failed.");
			uvd = NULL;
		}

		konicawc_register_input(cam, dev);
	}

	if (uvd) {
		usb_set_intfdata (intf, uvd);
		return 0;
	}
	return -EIO;
}