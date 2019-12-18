#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_11__ {scalar_t__ codec_id; int width; int height; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int swf_frame_number; int video_frame_number; int sound_samples; int /*<<< orphan*/  audio_fifo; scalar_t__ audio_par; int /*<<< orphan*/  vframes_pos; } ;
typedef  TYPE_1__ SWFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_FLV1 ; 
 scalar_t__ AV_CODEC_ID_MJPEG ; 
 scalar_t__ AV_CODEC_ID_VP6F ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int BITMAP_ID ; 
 int FRAC_BITS ; 
 int SHAPE_ID ; 
 int TAG_FREECHARACTER ; 
 int TAG_JPEG2 ; 
 int TAG_LONG ; 
 int TAG_PLACEOBJECT ; 
 int TAG_PLACEOBJECT2 ; 
 int TAG_REMOVEOBJECT ; 
 int TAG_SHOWFRAME ; 
 int TAG_STREAMBLOCK ; 
 int TAG_VIDEOFRAME ; 
 int TAG_VIDEOSTREAM ; 
 int VIDEO_ID ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char const*,int) ; 
 int ff_codec_get_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ff_swf_codec_tags ; 
 int /*<<< orphan*/  put_swf_end_tag (TYPE_2__*) ; 
 int /*<<< orphan*/  put_swf_matrix (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_swf_tag (TYPE_2__*,int) ; 

__attribute__((used)) static int swf_write_video(AVFormatContext *s,
                           AVCodecParameters *par, const uint8_t *buf, int size)
{
    SWFContext *swf = s->priv_data;
    AVIOContext *pb = s->pb;

    /* Flash Player limit */
    if (swf->swf_frame_number == 16000)
        av_log(s, AV_LOG_INFO, "warning: Flash Player limit of 16000 frames reached\n");

    if (par->codec_id == AV_CODEC_ID_VP6F ||
        par->codec_id == AV_CODEC_ID_FLV1) {
        if (swf->video_frame_number == 0) {
            /* create a new video object */
            put_swf_tag(s, TAG_VIDEOSTREAM);
            avio_wl16(pb, VIDEO_ID);
            swf->vframes_pos = avio_tell(pb);
            avio_wl16(pb, 15000); /* hard flash player limit */
            avio_wl16(pb, par->width);
            avio_wl16(pb, par->height);
            avio_w8(pb, 0);
            avio_w8(pb,ff_codec_get_tag(ff_swf_codec_tags, par->codec_id));
            put_swf_end_tag(s);

            /* place the video object for the first time */
            put_swf_tag(s, TAG_PLACEOBJECT2);
            avio_w8(pb, 0x36);
            avio_wl16(pb, 1);
            avio_wl16(pb, VIDEO_ID);
            put_swf_matrix(pb, 1 << FRAC_BITS, 0, 0, 1 << FRAC_BITS, 0, 0);
            avio_wl16(pb, swf->video_frame_number);
            avio_write(pb, "video", 5);
            avio_w8(pb, 0x00);
            put_swf_end_tag(s);
        } else {
            /* mark the character for update */
            put_swf_tag(s, TAG_PLACEOBJECT2);
            avio_w8(pb, 0x11);
            avio_wl16(pb, 1);
            avio_wl16(pb, swf->video_frame_number);
            put_swf_end_tag(s);
        }

        /* set video frame data */
        put_swf_tag(s, TAG_VIDEOFRAME | TAG_LONG);
        avio_wl16(pb, VIDEO_ID);
        avio_wl16(pb, swf->video_frame_number++);
        avio_write(pb, buf, size);
        put_swf_end_tag(s);
    } else if (par->codec_id == AV_CODEC_ID_MJPEG) {
        if (swf->swf_frame_number > 0) {
            /* remove the shape */
            put_swf_tag(s, TAG_REMOVEOBJECT);
            avio_wl16(pb, SHAPE_ID); /* shape ID */
            avio_wl16(pb, 1); /* depth */
            put_swf_end_tag(s);

            /* free the bitmap */
            put_swf_tag(s, TAG_FREECHARACTER);
            avio_wl16(pb, BITMAP_ID);
            put_swf_end_tag(s);
        }

        put_swf_tag(s, TAG_JPEG2 | TAG_LONG);

        avio_wl16(pb, BITMAP_ID); /* ID of the image */

        /* a dummy jpeg header seems to be required */
        avio_wb32(pb, 0xffd8ffd9);
        /* write the jpeg image */
        avio_write(pb, buf, size);

        put_swf_end_tag(s);

        /* draw the shape */

        put_swf_tag(s, TAG_PLACEOBJECT);
        avio_wl16(pb, SHAPE_ID); /* shape ID */
        avio_wl16(pb, 1); /* depth */
        put_swf_matrix(pb, 20 << FRAC_BITS, 0, 0, 20 << FRAC_BITS, 0, 0);
        put_swf_end_tag(s);
    }

    swf->swf_frame_number++;

    /* streaming sound always should be placed just before showframe tags */
    if (swf->audio_par && av_fifo_size(swf->audio_fifo)) {
        int frame_size = av_fifo_size(swf->audio_fifo);
        put_swf_tag(s, TAG_STREAMBLOCK | TAG_LONG);
        avio_wl16(pb, swf->sound_samples);
        avio_wl16(pb, 0); // seek samples
        av_fifo_generic_read(swf->audio_fifo, pb, frame_size, (void*)avio_write);
        put_swf_end_tag(s);

        /* update FIFO */
        swf->sound_samples = 0;
    }

    /* output the frame */
    put_swf_tag(s, TAG_SHOWFRAME);
    put_swf_end_tag(s);

    return 0;
}