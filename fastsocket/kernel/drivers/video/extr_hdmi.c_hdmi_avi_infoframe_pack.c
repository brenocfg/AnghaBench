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
typedef  int u8 ;
struct hdmi_avi_infoframe {size_t length; int type; int version; int colorspace; int scan_mode; int colorimetry; int picture_aspect; int active_aspect; int extended_colorimetry; int quantization_range; int nups; int video_code; int ycc_quantization_range; int content_type; int pixel_repeat; int top_bar; int bottom_bar; int left_bar; int right_bar; scalar_t__ itc; scalar_t__ vertical_bar_valid; scalar_t__ horizontal_bar_valid; scalar_t__ active_info_valid; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BIT (int) ; 
 size_t ENOSPC ; 
 size_t HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  hdmi_infoframe_checksum (void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

ssize_t hdmi_avi_infoframe_pack(struct hdmi_avi_infoframe *frame, void *buffer,
				size_t size)
{
	u8 *ptr = buffer;
	size_t length;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	if (size < length)
		return -ENOSPC;

	memset(buffer, 0, length);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	ptr[0] = ((frame->colorspace & 0x3) << 5) | (frame->scan_mode & 0x3);

	if (frame->active_info_valid)
		ptr[0] |= BIT(4);

	if (frame->horizontal_bar_valid)
		ptr[0] |= BIT(3);

	if (frame->vertical_bar_valid)
		ptr[0] |= BIT(2);

	ptr[1] = ((frame->colorimetry & 0x3) << 6) |
		 ((frame->picture_aspect & 0x3) << 4) |
		 (frame->active_aspect & 0xf);

	ptr[2] = ((frame->extended_colorimetry & 0x7) << 4) |
		 ((frame->quantization_range & 0x3) << 2) |
		 (frame->nups & 0x3);

	if (frame->itc)
		ptr[2] |= BIT(7);

	ptr[3] = frame->video_code & 0x7f;

	ptr[4] = ((frame->ycc_quantization_range & 0x3) << 6) |
		 ((frame->content_type & 0x3) << 4) |
		 (frame->pixel_repeat & 0xf);

	ptr[5] = frame->top_bar & 0xff;
	ptr[6] = (frame->top_bar >> 8) & 0xff;
	ptr[7] = frame->bottom_bar & 0xff;
	ptr[8] = (frame->bottom_bar >> 8) & 0xff;
	ptr[9] = frame->left_bar & 0xff;
	ptr[10] = (frame->left_bar >> 8) & 0xff;
	ptr[11] = frame->right_bar & 0xff;
	ptr[12] = (frame->right_bar >> 8) & 0xff;

	hdmi_infoframe_checksum(buffer, length);

	return length;
}