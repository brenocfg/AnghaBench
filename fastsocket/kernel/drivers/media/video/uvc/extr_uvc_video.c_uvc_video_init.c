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
struct uvc_streaming_control {scalar_t__ bFormatIndex; scalar_t__ bFrameIndex; } ;
struct uvc_streaming {unsigned int nformats; scalar_t__ type; int /*<<< orphan*/  decode; TYPE_2__* intf; TYPE_1__* dev; struct uvc_frame* cur_frame; struct uvc_format* cur_format; struct uvc_format* format; int /*<<< orphan*/  intfnum; int /*<<< orphan*/  queue; int /*<<< orphan*/  active; struct uvc_streaming_control ctrl; } ;
struct uvc_frame {scalar_t__ bFrameIndex; } ;
struct uvc_format {scalar_t__ index; unsigned int nframes; struct uvc_frame* frame; } ;
struct TYPE_4__ {int num_altsetting; } ;
struct TYPE_3__ {int quirks; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  UVC_GET_CUR ; 
 int /*<<< orphan*/  UVC_GET_DEF ; 
 int UVC_QUIRK_BUILTIN_ISIGHT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uvc_get_video_ctrl (struct uvc_streaming*,struct uvc_streaming_control*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_no_drop_param ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uvc_queue_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  uvc_set_video_ctrl (struct uvc_streaming*,struct uvc_streaming_control*,int) ; 
 int /*<<< orphan*/  uvc_video_decode_bulk ; 
 int /*<<< orphan*/  uvc_video_decode_isight ; 
 int /*<<< orphan*/  uvc_video_decode_isoc ; 
 int /*<<< orphan*/  uvc_video_encode_bulk ; 

int uvc_video_init(struct uvc_streaming *stream)
{
	struct uvc_streaming_control *probe = &stream->ctrl;
	struct uvc_format *format = NULL;
	struct uvc_frame *frame = NULL;
	unsigned int i;
	int ret;

	if (stream->nformats == 0) {
		uvc_printk(KERN_INFO, "No supported video formats found.\n");
		return -EINVAL;
	}

	atomic_set(&stream->active, 0);

	/* Initialize the video buffers queue. */
	uvc_queue_init(&stream->queue, stream->type, !uvc_no_drop_param);

	/* Alternate setting 0 should be the default, yet the XBox Live Vision
	 * Cam (and possibly other devices) crash or otherwise misbehave if
	 * they don't receive a SET_INTERFACE request before any other video
	 * control request.
	 */
	usb_set_interface(stream->dev->udev, stream->intfnum, 0);

	/* Set the streaming probe control with default streaming parameters
	 * retrieved from the device. Webcams that don't suport GET_DEF
	 * requests on the probe control will just keep their current streaming
	 * parameters.
	 */
	if (uvc_get_video_ctrl(stream, probe, 1, UVC_GET_DEF) == 0)
		uvc_set_video_ctrl(stream, probe, 1);

	/* Initialize the streaming parameters with the probe control current
	 * value. This makes sure SET_CUR requests on the streaming commit
	 * control will always use values retrieved from a successful GET_CUR
	 * request on the probe control, as required by the UVC specification.
	 */
	ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
	if (ret < 0)
		return ret;

	/* Check if the default format descriptor exists. Use the first
	 * available format otherwise.
	 */
	for (i = stream->nformats; i > 0; --i) {
		format = &stream->format[i-1];
		if (format->index == probe->bFormatIndex)
			break;
	}

	if (format->nframes == 0) {
		uvc_printk(KERN_INFO, "No frame descriptor found for the "
			"default format.\n");
		return -EINVAL;
	}

	/* Zero bFrameIndex might be correct. Stream-based formats (including
	 * MPEG-2 TS and DV) do not support frames but have a dummy frame
	 * descriptor with bFrameIndex set to zero. If the default frame
	 * descriptor is not found, use the first available frame.
	 */
	for (i = format->nframes; i > 0; --i) {
		frame = &format->frame[i-1];
		if (frame->bFrameIndex == probe->bFrameIndex)
			break;
	}

	probe->bFormatIndex = format->index;
	probe->bFrameIndex = frame->bFrameIndex;

	stream->cur_format = format;
	stream->cur_frame = frame;

	/* Select the video decoding function */
	if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		if (stream->dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)
			stream->decode = uvc_video_decode_isight;
		else if (stream->intf->num_altsetting > 1)
			stream->decode = uvc_video_decode_isoc;
		else
			stream->decode = uvc_video_decode_bulk;
	} else {
		if (stream->intf->num_altsetting == 1)
			stream->decode = uvc_video_encode_bulk;
		else {
			uvc_printk(KERN_INFO, "Isochronous endpoints are not "
				"supported for video output devices.\n");
			return -EINVAL;
		}
	}

	return 0;
}