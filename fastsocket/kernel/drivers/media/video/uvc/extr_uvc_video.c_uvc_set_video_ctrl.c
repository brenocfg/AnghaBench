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
struct uvc_streaming_control {scalar_t__ bMaxVersion; scalar_t__ bMinVersion; scalar_t__ bPreferedVersion; scalar_t__ bmFramingInfo; int /*<<< orphan*/  dwClockFrequency; int /*<<< orphan*/  dwMaxPayloadTransferSize; int /*<<< orphan*/  dwMaxVideoFrameSize; int /*<<< orphan*/  wDelay; int /*<<< orphan*/  wCompWindowSize; int /*<<< orphan*/  wCompQuality; int /*<<< orphan*/  wPFrameRate; int /*<<< orphan*/  wKeyFrameRate; int /*<<< orphan*/  dwFrameInterval; scalar_t__ bFrameIndex; scalar_t__ bFormatIndex; int /*<<< orphan*/  bmHint; } ;
struct uvc_streaming {int /*<<< orphan*/  intfnum; TYPE_1__* dev; } ;
typedef  scalar_t__ __u8 ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int uvc_version; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  UVC_SET_CUR ; 
 int /*<<< orphan*/  UVC_VS_COMMIT_CONTROL ; 
 int /*<<< orphan*/  UVC_VS_PROBE_CONTROL ; 
 int __uvc_query_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  uvc_timeout_param ; 

__attribute__((used)) static int uvc_set_video_ctrl(struct uvc_streaming *stream,
	struct uvc_streaming_control *ctrl, int probe)
{
	__u8 *data;
	__u16 size;
	int ret;

	size = stream->dev->uvc_version >= 0x0110 ? 34 : 26;
	data = kzalloc(size, GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	*(__le16 *)&data[0] = cpu_to_le16(ctrl->bmHint);
	data[2] = ctrl->bFormatIndex;
	data[3] = ctrl->bFrameIndex;
	*(__le32 *)&data[4] = cpu_to_le32(ctrl->dwFrameInterval);
	*(__le16 *)&data[8] = cpu_to_le16(ctrl->wKeyFrameRate);
	*(__le16 *)&data[10] = cpu_to_le16(ctrl->wPFrameRate);
	*(__le16 *)&data[12] = cpu_to_le16(ctrl->wCompQuality);
	*(__le16 *)&data[14] = cpu_to_le16(ctrl->wCompWindowSize);
	*(__le16 *)&data[16] = cpu_to_le16(ctrl->wDelay);
	put_unaligned_le32(ctrl->dwMaxVideoFrameSize, &data[18]);
	put_unaligned_le32(ctrl->dwMaxPayloadTransferSize, &data[22]);

	if (size == 34) {
		put_unaligned_le32(ctrl->dwClockFrequency, &data[26]);
		data[30] = ctrl->bmFramingInfo;
		data[31] = ctrl->bPreferedVersion;
		data[32] = ctrl->bMinVersion;
		data[33] = ctrl->bMaxVersion;
	}

	ret = __uvc_query_ctrl(stream->dev, UVC_SET_CUR, 0, stream->intfnum,
		probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
		size, uvc_timeout_param);
	if (ret != size) {
		uvc_printk(KERN_ERR, "Failed to set UVC %s control : "
			"%d (exp. %u).\n", probe ? "probe" : "commit",
			ret, size);
		ret = -EIO;
	}

	kfree(data);
	return ret;
}