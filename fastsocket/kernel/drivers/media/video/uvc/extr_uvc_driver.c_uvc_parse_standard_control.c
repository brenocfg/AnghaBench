#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned char bNumControls; unsigned char bControlSize; int /*<<< orphan*/ * bmControls; int /*<<< orphan*/ * guidExtensionCode; } ;
struct TYPE_10__ {unsigned char bControlSize; unsigned char bmVideoStandards; int /*<<< orphan*/ * bmControls; void* wMaxMultiplier; } ;
struct TYPE_9__ {unsigned int bControlSize; unsigned int bTransportModeSize; int /*<<< orphan*/ * bmTransportModes; int /*<<< orphan*/ * bmControls; } ;
struct TYPE_8__ {unsigned int bControlSize; int /*<<< orphan*/ * bmControls; void* wOcularFocalLength; void* wObjectiveFocalLengthMax; void* wObjectiveFocalLengthMin; } ;
struct uvc_entity {int /*<<< orphan*/  list; int /*<<< orphan*/  name; TYPE_6__ extension; int /*<<< orphan*/ * baSourceID; TYPE_4__ processing; TYPE_3__ media; TYPE_2__ camera; } ;
struct uvc_device {int uvc_version; int /*<<< orphan*/  entities; int /*<<< orphan*/  clock_frequency; TYPE_1__* intf; struct usb_device* udev; } ;
struct usb_interface {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_5__ desc; } ;
struct usb_device {int /*<<< orphan*/  devnum; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;
struct TYPE_7__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int UVC_ENTITY_TYPE (struct uvc_entity*) ; 
 int UVC_ITT_CAMERA ; 
 int UVC_ITT_MEDIA_TRANSPORT_INPUT ; 
 int UVC_TERM_INPUT ; 
 int UVC_TERM_OUTPUT ; 
 int /*<<< orphan*/  UVC_TRACE_DESCR ; 
#define  UVC_VC_EXTENSION_UNIT 133 
#define  UVC_VC_HEADER 132 
#define  UVC_VC_INPUT_TERMINAL 131 
#define  UVC_VC_OUTPUT_TERMINAL 130 
#define  UVC_VC_PROCESSING_UNIT 129 
#define  UVC_VC_SELECTOR_UNIT 128 
 void* get_unaligned_le16 (unsigned char const*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (unsigned char const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned char const) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,unsigned char const) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,unsigned char const,int /*<<< orphan*/ ,int) ; 
 struct uvc_entity* uvc_alloc_entity (unsigned char const,unsigned char const,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uvc_parse_streaming (struct uvc_device*,struct usb_interface*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,unsigned char const,...) ; 

__attribute__((used)) static int uvc_parse_standard_control(struct uvc_device *dev,
	const unsigned char *buffer, int buflen)
{
	struct usb_device *udev = dev->udev;
	struct uvc_entity *unit, *term;
	struct usb_interface *intf;
	struct usb_host_interface *alts = dev->intf->cur_altsetting;
	unsigned int i, n, p, len;
	__u16 type;

	switch (buffer[2]) {
	case UVC_VC_HEADER:
		n = buflen >= 12 ? buffer[11] : 0;

		if (buflen < 12 || buflen < 12 + n) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d HEADER error\n", udev->devnum,
				alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		dev->uvc_version = get_unaligned_le16(&buffer[3]);
		dev->clock_frequency = get_unaligned_le32(&buffer[7]);

		/* Parse all USB Video Streaming interfaces. */
		for (i = 0; i < n; ++i) {
			intf = usb_ifnum_to_if(udev, buffer[12+i]);
			if (intf == NULL) {
				uvc_trace(UVC_TRACE_DESCR, "device %d "
					"interface %d doesn't exists\n",
					udev->devnum, i);
				continue;
			}

			uvc_parse_streaming(dev, intf);
		}
		break;

	case UVC_VC_INPUT_TERMINAL:
		if (buflen < 8) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d INPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		/* Make sure the terminal type MSB is not null, otherwise it
		 * could be confused with a unit.
		 */
		type = get_unaligned_le16(&buffer[4]);
		if ((type & 0xff00) == 0) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d INPUT_TERMINAL %d has invalid "
				"type 0x%04x, skipping\n", udev->devnum,
				alts->desc.bInterfaceNumber,
				buffer[3], type);
			return 0;
		}

		n = 0;
		p = 0;
		len = 8;

		if (type == UVC_ITT_CAMERA) {
			n = buflen >= 15 ? buffer[14] : 0;
			len = 15;

		} else if (type == UVC_ITT_MEDIA_TRANSPORT_INPUT) {
			n = buflen >= 9 ? buffer[8] : 0;
			p = buflen >= 10 + n ? buffer[9+n] : 0;
			len = 10;
		}

		if (buflen < len + n + p) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d INPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		term = uvc_alloc_entity(type | UVC_TERM_INPUT, buffer[3],
					1, n + p);
		if (term == NULL)
			return -ENOMEM;

		if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA) {
			term->camera.bControlSize = n;
			term->camera.bmControls = (__u8 *)term + sizeof *term;
			term->camera.wObjectiveFocalLengthMin =
				get_unaligned_le16(&buffer[8]);
			term->camera.wObjectiveFocalLengthMax =
				get_unaligned_le16(&buffer[10]);
			term->camera.wOcularFocalLength =
				get_unaligned_le16(&buffer[12]);
			memcpy(term->camera.bmControls, &buffer[15], n);
		} else if (UVC_ENTITY_TYPE(term) ==
			   UVC_ITT_MEDIA_TRANSPORT_INPUT) {
			term->media.bControlSize = n;
			term->media.bmControls = (__u8 *)term + sizeof *term;
			term->media.bTransportModeSize = p;
			term->media.bmTransportModes = (__u8 *)term
						     + sizeof *term + n;
			memcpy(term->media.bmControls, &buffer[9], n);
			memcpy(term->media.bmTransportModes, &buffer[10+n], p);
		}

		if (buffer[7] != 0)
			usb_string(udev, buffer[7], term->name,
				   sizeof term->name);
		else if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA)
			sprintf(term->name, "Camera %u", buffer[3]);
		else if (UVC_ENTITY_TYPE(term) == UVC_ITT_MEDIA_TRANSPORT_INPUT)
			sprintf(term->name, "Media %u", buffer[3]);
		else
			sprintf(term->name, "Input %u", buffer[3]);

		list_add_tail(&term->list, &dev->entities);
		break;

	case UVC_VC_OUTPUT_TERMINAL:
		if (buflen < 9) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d OUTPUT_TERMINAL error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		/* Make sure the terminal type MSB is not null, otherwise it
		 * could be confused with a unit.
		 */
		type = get_unaligned_le16(&buffer[4]);
		if ((type & 0xff00) == 0) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d OUTPUT_TERMINAL %d has invalid "
				"type 0x%04x, skipping\n", udev->devnum,
				alts->desc.bInterfaceNumber, buffer[3], type);
			return 0;
		}

		term = uvc_alloc_entity(type | UVC_TERM_OUTPUT, buffer[3],
					1, 0);
		if (term == NULL)
			return -ENOMEM;

		memcpy(term->baSourceID, &buffer[7], 1);

		if (buffer[8] != 0)
			usb_string(udev, buffer[8], term->name,
				   sizeof term->name);
		else
			sprintf(term->name, "Output %u", buffer[3]);

		list_add_tail(&term->list, &dev->entities);
		break;

	case UVC_VC_SELECTOR_UNIT:
		p = buflen >= 5 ? buffer[4] : 0;

		if (buflen < 5 || buflen < 6 + p) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d SELECTOR_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, 0);
		if (unit == NULL)
			return -ENOMEM;

		memcpy(unit->baSourceID, &buffer[5], p);

		if (buffer[5+p] != 0)
			usb_string(udev, buffer[5+p], unit->name,
				   sizeof unit->name);
		else
			sprintf(unit->name, "Selector %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		break;

	case UVC_VC_PROCESSING_UNIT:
		n = buflen >= 8 ? buffer[7] : 0;
		p = dev->uvc_version >= 0x0110 ? 10 : 9;

		if (buflen < p + n) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d PROCESSING_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		unit = uvc_alloc_entity(buffer[2], buffer[3], 2, n);
		if (unit == NULL)
			return -ENOMEM;

		memcpy(unit->baSourceID, &buffer[4], 1);
		unit->processing.wMaxMultiplier =
			get_unaligned_le16(&buffer[5]);
		unit->processing.bControlSize = buffer[7];
		unit->processing.bmControls = (__u8 *)unit + sizeof *unit;
		memcpy(unit->processing.bmControls, &buffer[8], n);
		if (dev->uvc_version >= 0x0110)
			unit->processing.bmVideoStandards = buffer[9+n];

		if (buffer[8+n] != 0)
			usb_string(udev, buffer[8+n], unit->name,
				   sizeof unit->name);
		else
			sprintf(unit->name, "Processing %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		break;

	case UVC_VC_EXTENSION_UNIT:
		p = buflen >= 22 ? buffer[21] : 0;
		n = buflen >= 24 + p ? buffer[22+p] : 0;

		if (buflen < 24 + p + n) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d EXTENSION_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			return -EINVAL;
		}

		unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, n);
		if (unit == NULL)
			return -ENOMEM;

		memcpy(unit->extension.guidExtensionCode, &buffer[4], 16);
		unit->extension.bNumControls = buffer[20];
		memcpy(unit->baSourceID, &buffer[22], p);
		unit->extension.bControlSize = buffer[22+p];
		unit->extension.bmControls = (__u8 *)unit + sizeof *unit;
		memcpy(unit->extension.bmControls, &buffer[23+p], n);

		if (buffer[23+p+n] != 0)
			usb_string(udev, buffer[23+p+n], unit->name,
				   sizeof unit->name);
		else
			sprintf(unit->name, "Extension %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		break;

	default:
		uvc_trace(UVC_TRACE_DESCR, "Found an unknown CS_INTERFACE "
			"descriptor (%u)\n", buffer[2]);
		break;
	}

	return 0;
}