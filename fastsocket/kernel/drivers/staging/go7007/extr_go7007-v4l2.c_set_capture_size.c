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
typedef  int u32 ;
struct video_decoder_resolution {int width; int height; } ;
struct TYPE_7__ {int pixelformat; int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  field; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; int /*<<< orphan*/  type; } ;
struct go7007 {int standard; int width; int height; int encoder_v_halve; int encoder_h_halve; int encoder_subsample; int pali; int gop_size; int sensor_framerate; int closed_gop; int repeat_seqhead; int seq_header_enable; int gop_header_enable; int /*<<< orphan*/  dvd_mode; int /*<<< orphan*/  ipb; void* aspect_ratio; int /*<<< orphan*/  format; int /*<<< orphan*/  i2c_adapter; scalar_t__ i2c_adapter_online; TYPE_2__* board_info; scalar_t__* modet_map; TYPE_1__* modet; int /*<<< orphan*/  encoder_v_offset; int /*<<< orphan*/  encoder_h_offset; } ;
struct TYPE_6__ {int sensor_width; int sensor_height; int sensor_flags; int /*<<< orphan*/  sensor_v_offset; int /*<<< orphan*/  sensor_h_offset; } ;
struct TYPE_5__ {scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECODER_SET_RESOLUTION ; 
 int EINVAL ; 
 int /*<<< orphan*/  GO7007_BUF_SIZE ; 
 int /*<<< orphan*/  GO7007_FORMAT_MJPEG ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG1 ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG2 ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG4 ; 
 void* GO7007_RATIO_1_1 ; 
 int GO7007_SENSOR_SCALING ; 
#define  GO7007_STD_NTSC 133 
#define  GO7007_STD_OTHER 132 
#define  GO7007_STD_PAL 131 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_MJPEG 130 
#define  V4L2_PIX_FMT_MPEG 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct video_decoder_resolution*) ; 
 int /*<<< orphan*/  memset (struct v4l2_format*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_capture_size(struct go7007 *go, struct v4l2_format *fmt, int try)
{
	int sensor_height = 0, sensor_width = 0;
	int width, height, i;

	if (fmt != NULL && fmt->fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG &&
			fmt->fmt.pix.pixelformat != V4L2_PIX_FMT_MPEG &&
			fmt->fmt.pix.pixelformat != V4L2_PIX_FMT_MPEG4)
		return -EINVAL;

	switch (go->standard) {
	case GO7007_STD_NTSC:
		sensor_width = 720;
		sensor_height = 480;
		break;
	case GO7007_STD_PAL:
		sensor_width = 720;
		sensor_height = 576;
		break;
	case GO7007_STD_OTHER:
		sensor_width = go->board_info->sensor_width;
		sensor_height = go->board_info->sensor_height;
		break;
	}

	if (fmt == NULL) {
		width = sensor_width;
		height = sensor_height;
	} else if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) {
		if (fmt->fmt.pix.width > sensor_width)
			width = sensor_width;
		else if (fmt->fmt.pix.width < 144)
			width = 144;
		else
			width = fmt->fmt.pix.width & ~0x0f;

		if (fmt->fmt.pix.height > sensor_height)
			height = sensor_height;
		else if (fmt->fmt.pix.height < 96)
			height = 96;
		else
			height = fmt->fmt.pix.height & ~0x0f;
	} else {
		int requested_size = fmt->fmt.pix.width * fmt->fmt.pix.height;
		int sensor_size = sensor_width * sensor_height;

		if (64 * requested_size < 9 * sensor_size) {
			width = sensor_width / 4;
			height = sensor_height / 4;
		} else if (64 * requested_size < 36 * sensor_size) {
			width = sensor_width / 2;
			height = sensor_height / 2;
		} else {
			width = sensor_width;
			height = sensor_height;
		}
		width &= ~0xf;
		height &= ~0xf;
	}

	if (fmt != NULL) {
		u32 pixelformat = fmt->fmt.pix.pixelformat;

		memset(fmt, 0, sizeof(*fmt));
		fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt->fmt.pix.width = width;
		fmt->fmt.pix.height = height;
		fmt->fmt.pix.pixelformat = pixelformat;
		fmt->fmt.pix.field = V4L2_FIELD_NONE;
		fmt->fmt.pix.bytesperline = 0;
		fmt->fmt.pix.sizeimage = GO7007_BUF_SIZE;
		fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M; /* ?? */
	}

	if (try)
		return 0;

	go->width = width;
	go->height = height;
	go->encoder_h_offset = go->board_info->sensor_h_offset;
	go->encoder_v_offset = go->board_info->sensor_v_offset;
	for (i = 0; i < 4; ++i)
		go->modet[i].enable = 0;
	for (i = 0; i < 1624; ++i)
		go->modet_map[i] = 0;

	if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING) {
		struct video_decoder_resolution res;

		res.width = width;
		if (height > sensor_height / 2) {
			res.height = height / 2;
			go->encoder_v_halve = 0;
		} else {
			res.height = height;
			go->encoder_v_halve = 1;
		}
		if (go->i2c_adapter_online)
			i2c_clients_command(&go->i2c_adapter,
					DECODER_SET_RESOLUTION, &res);
	} else {
		if (width <= sensor_width / 4) {
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 1;
		} else if (width <= sensor_width / 2) {
			go->encoder_h_halve = 1;
			go->encoder_v_halve = 1;
			go->encoder_subsample = 0;
		} else {
			go->encoder_h_halve = 0;
			go->encoder_v_halve = 0;
			go->encoder_subsample = 0;
		}
	}

	if (fmt == NULL)
		return 0;

	switch (fmt->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_MPEG:
		if (go->format == GO7007_FORMAT_MPEG1 ||
				go->format == GO7007_FORMAT_MPEG2 ||
				go->format == GO7007_FORMAT_MPEG4)
			break;
		go->format = GO7007_FORMAT_MPEG1;
		go->pali = 0;
		go->aspect_ratio = GO7007_RATIO_1_1;
		go->gop_size = go->sensor_framerate / 1000;
		go->ipb = 0;
		go->closed_gop = 1;
		go->repeat_seqhead = 1;
		go->seq_header_enable = 1;
		go->gop_header_enable = 1;
		go->dvd_mode = 0;
		break;
	/* Backwards compatibility only! */
	case V4L2_PIX_FMT_MPEG4:
		if (go->format == GO7007_FORMAT_MPEG4)
			break;
		go->format = GO7007_FORMAT_MPEG4;
		go->pali = 0xf5;
		go->aspect_ratio = GO7007_RATIO_1_1;
		go->gop_size = go->sensor_framerate / 1000;
		go->ipb = 0;
		go->closed_gop = 1;
		go->repeat_seqhead = 1;
		go->seq_header_enable = 1;
		go->gop_header_enable = 1;
		go->dvd_mode = 0;
		break;
	case V4L2_PIX_FMT_MJPEG:
		go->format = GO7007_FORMAT_MJPEG;
		go->pali = 0;
		go->aspect_ratio = GO7007_RATIO_1_1;
		go->gop_size = 0;
		go->ipb = 0;
		go->closed_gop = 0;
		go->repeat_seqhead = 0;
		go->seq_header_enable = 0;
		go->gop_header_enable = 0;
		go->dvd_mode = 0;
		break;
	}
	return 0;
}