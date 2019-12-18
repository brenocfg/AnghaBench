#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct urb {int /*<<< orphan*/  status; struct gtco* context; } ;
struct TYPE_2__ {scalar_t__ product; } ;
struct input_dev {TYPE_1__ id; } ;
struct gtco {int* buffer; int max_X; struct input_dev* inputdevice; } ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 scalar_t__ BTN_DIGI ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MASK_BUTTON ; 
 char MASK_INRANGE ; 
 int /*<<< orphan*/  MSC_RAW ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 scalar_t__ PID_1000 ; 
 scalar_t__ PID_1001 ; 
 scalar_t__ PID_1002 ; 
 scalar_t__ PID_400 ; 
 scalar_t__ PID_401 ; 
 int /*<<< orphan*/  dbg (char*,int,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int get_unaligned_le16 (char*) ; 
 int i ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gtco_urb_callback(struct urb *urbinfo)
{
	struct gtco *device = urbinfo->context;
	struct input_dev  *inputdev;
	int               rc;
	u32               val = 0;
	s8                valsigned = 0;
	char              le_buffer[2];

	inputdev = device->inputdevice;

	/* Was callback OK? */
	if (urbinfo->status == -ECONNRESET ||
	    urbinfo->status == -ENOENT ||
	    urbinfo->status == -ESHUTDOWN) {

		/* Shutdown is occurring. Return and don't queue up any more */
		return;
	}

	if (urbinfo->status != 0) {
		/*
		 * Some unknown error.  Hopefully temporary. Just go and
		 * requeue an URB
		 */
		goto resubmit;
	}

	/*
	 * Good URB, now process
	 */

	/* PID dependent when we interpret the report */
	if (inputdev->id.product == PID_1000 ||
	    inputdev->id.product == PID_1001 ||
	    inputdev->id.product == PID_1002) {

		/*
		 * Switch on the report ID
		 * Conveniently, the reports have more information, the higher
		 * the report number.  We can just fall through the case
		 * statements if we start with the highest number report
		 */
		switch (device->buffer[0]) {
		case 5:
			/* Pressure is 9 bits */
			val = ((u16)(device->buffer[8]) << 1);
			val |= (u16)(device->buffer[7] >> 7);
			input_report_abs(inputdev, ABS_PRESSURE,
					 device->buffer[8]);

			/* Mask out the Y tilt value used for pressure */
			device->buffer[7] = (u8)((device->buffer[7]) & 0x7F);

			/* Fall thru */
		case 4:
			/* Tilt */

			/* Sign extend these 7 bit numbers.  */
			if (device->buffer[6] & 0x40)
				device->buffer[6] |= 0x80;

			if (device->buffer[7] & 0x40)
				device->buffer[7] |= 0x80;


			valsigned = (device->buffer[6]);
			input_report_abs(inputdev, ABS_TILT_X, (s32)valsigned);

			valsigned = (device->buffer[7]);
			input_report_abs(inputdev, ABS_TILT_Y, (s32)valsigned);

			/* Fall thru */
		case 2:
		case 3:
			/* Convert buttons, only 5 bits possible */
			val = (device->buffer[5]) & MASK_BUTTON;

			/* We don't apply any meaning to the bitmask,
			   just report */
			input_event(inputdev, EV_MSC, MSC_SERIAL, val);

			/*  Fall thru */
		case 1:
			/* All reports have X and Y coords in the same place */
			val = get_unaligned_le16(&device->buffer[1]);
			input_report_abs(inputdev, ABS_X, val);

			val = get_unaligned_le16(&device->buffer[3]);
			input_report_abs(inputdev, ABS_Y, val);

			/* Ditto for proximity bit */
			val = device->buffer[5] & MASK_INRANGE ? 1 : 0;
			input_report_abs(inputdev, ABS_DISTANCE, val);

			/* Report 1 is an exception to how we handle buttons */
			/* Buttons are an index, not a bitmask */
			if (device->buffer[0] == 1) {

				/*
				 * Convert buttons, 5 bit index
				 * Report value of index set as one,
				 * the rest as 0
				 */
				val = device->buffer[5] & MASK_BUTTON;
				dbg("======>>>>>>REPORT 1: val 0x%X(%d)",
				    val, val);

				/*
				 * We don't apply any meaning to the button
				 * index, just report it
				 */
				input_event(inputdev, EV_MSC, MSC_SERIAL, val);
			}
			break;

		case 7:
			/* Menu blocks */
			input_event(inputdev, EV_MSC, MSC_SCAN,
				    device->buffer[1]);
			break;
		}
	}

	/* Other pid class */
	if (inputdev->id.product == PID_400 ||
	    inputdev->id.product == PID_401) {

		/* Report 2 */
		if (device->buffer[0] == 2) {
			/* Menu blocks */
			input_event(inputdev, EV_MSC, MSC_SCAN, device->buffer[1]);
		}

		/*  Report 1 */
		if (device->buffer[0] == 1) {
			char buttonbyte;

			/*  IF X max > 64K, we still a bit from the y report */
			if (device->max_X > 0x10000) {

				val = (u16)(((u16)(device->buffer[2] << 8)) | (u8)device->buffer[1]);
				val |= (u32)(((u8)device->buffer[3] & 0x1) << 16);

				input_report_abs(inputdev, ABS_X, val);

				le_buffer[0]  = (u8)((u8)(device->buffer[3]) >> 1);
				le_buffer[0] |= (u8)((device->buffer[3] & 0x1) << 7);

				le_buffer[1]  = (u8)(device->buffer[4] >> 1);
				le_buffer[1] |= (u8)((device->buffer[5] & 0x1) << 7);

				val = get_unaligned_le16(le_buffer);
				input_report_abs(inputdev, ABS_Y, val);

				/*
				 * Shift the button byte right by one to
				 * make it look like the standard report
				 */
				buttonbyte = device->buffer[5] >> 1;
			} else {

				val = get_unaligned_le16(&device->buffer[1]);
				input_report_abs(inputdev, ABS_X, val);

				val = get_unaligned_le16(&device->buffer[3]);
				input_report_abs(inputdev, ABS_Y, val);

				buttonbyte = device->buffer[5];
			}

			/* BUTTONS and PROXIMITY */
			val = buttonbyte & MASK_INRANGE ? 1 : 0;
			input_report_abs(inputdev, ABS_DISTANCE, val);

			/* Convert buttons, only 4 bits possible */
			val = buttonbyte & 0x0F;
#ifdef USE_BUTTONS
			for (i = 0; i < 5; i++)
				input_report_key(inputdev, BTN_DIGI + i, val & (1 << i));
#else
			/* We don't apply any meaning to the bitmask, just report */
			input_event(inputdev, EV_MSC, MSC_SERIAL, val);
#endif

			/* TRANSDUCER */
			input_report_abs(inputdev, ABS_MISC, device->buffer[6]);
		}
	}

	/* Everybody gets report ID's */
	input_event(inputdev, EV_MSC, MSC_RAW,  device->buffer[0]);

	/* Sync it up */
	input_sync(inputdev);

 resubmit:
	rc = usb_submit_urb(urbinfo, GFP_ATOMIC);
	if (rc != 0)
		err("usb_submit_urb failed rc=0x%x", rc);
}