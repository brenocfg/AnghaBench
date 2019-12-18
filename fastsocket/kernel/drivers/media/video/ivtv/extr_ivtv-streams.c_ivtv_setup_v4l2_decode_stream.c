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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ivtv_stream {int type; int /*<<< orphan*/ * vdev; struct ivtv* itv; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  audio_properties; } ;
struct TYPE_3__ {int /*<<< orphan*/  dec_start; } ;
struct ivtv {TYPE_2__ cxhdl; int /*<<< orphan*/  is_out_50hz; int /*<<< orphan*/  output_mode; TYPE_1__ vbi; int /*<<< orphan*/  audio_stereo_mode; int /*<<< orphan*/  audio_bilingual_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_DEC_EXTRACT_VBI ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_AUDIO_MODE ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_DECODER_SOURCE ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_DISPLAY_BUFFERS ; 
 int /*<<< orphan*/  CX2341X_DEC_SET_PREBUFFERING ; 
 int CX2341X_MBOX_MAX_DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*) ; 
#define  IVTV_DEC_STREAM_TYPE_MPG 129 
#define  IVTV_DEC_STREAM_TYPE_YUV 128 
 int /*<<< orphan*/  OUT_PASSTHROUGH ; 
 int ivtv_firmware_check (struct ivtv*,char*) ; 
 int /*<<< orphan*/  ivtv_msleep_timeout (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  ivtv_vapi_result (struct ivtv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ivtv_setup_v4l2_decode_stream(struct ivtv_stream *s)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	struct ivtv *itv = s->itv;
	int datatype;
	u16 width;
	u16 height;

	if (s->vdev == NULL)
		return -EINVAL;

	IVTV_DEBUG_INFO("Setting some initial decoder settings\n");

	width = itv->cxhdl.width;
	height = itv->cxhdl.height;

	/* set audio mode to left/stereo  for dual/stereo mode. */
	ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_bilingual_mode, itv->audio_stereo_mode);

	/* set number of internal decoder buffers */
	ivtv_vapi(itv, CX2341X_DEC_SET_DISPLAY_BUFFERS, 1, 0);

	/* prebuffering */
	ivtv_vapi(itv, CX2341X_DEC_SET_PREBUFFERING, 1, 1);

	/* extract from user packets */
	ivtv_vapi_result(itv, data, CX2341X_DEC_EXTRACT_VBI, 1, 1);
	itv->vbi.dec_start = data[0];

	IVTV_DEBUG_INFO("Decoder VBI RE-Insert start 0x%08x size 0x%08x\n",
		itv->vbi.dec_start, data[1]);

	/* set decoder source settings */
	/* Data type: 0 = mpeg from host,
	   1 = yuv from encoder,
	   2 = yuv_from_host */
	switch (s->type) {
	case IVTV_DEC_STREAM_TYPE_YUV:
		if (itv->output_mode == OUT_PASSTHROUGH) {
			datatype = 1;
		} else {
			/* Fake size to avoid switching video standard */
			datatype = 2;
			width = 720;
			height = itv->is_out_50hz ? 576 : 480;
		}
		IVTV_DEBUG_INFO("Setup DEC YUV Stream data[0] = %d\n", datatype);
		break;
	case IVTV_DEC_STREAM_TYPE_MPG:
	default:
		datatype = 0;
		break;
	}
	if (ivtv_vapi(itv, CX2341X_DEC_SET_DECODER_SOURCE, 4, datatype,
			width, height, itv->cxhdl.audio_properties)) {
		IVTV_DEBUG_WARN("Couldn't initialize decoder source\n");
	}

	/* Decoder sometimes dies here, so wait a moment */
	ivtv_msleep_timeout(10, 0);

	/* Known failure point for firmware, so check */
	return ivtv_firmware_check(itv, "ivtv_setup_v4l2_decode_stream");
}