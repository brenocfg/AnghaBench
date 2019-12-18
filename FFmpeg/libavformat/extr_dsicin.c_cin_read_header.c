#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_14__ {TYPE_1__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_12__ {int /*<<< orphan*/  video_frame_height; int /*<<< orphan*/  video_frame_width; } ;
struct TYPE_13__ {int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  video_stream_index; scalar_t__ audio_buffer_size; scalar_t__ audio_stream_pts; scalar_t__ video_stream_pts; TYPE_2__ file_header; } ;
struct TYPE_11__ {int channels; int sample_rate; int bits_per_coded_sample; int bit_rate; int /*<<< orphan*/  channel_layout; scalar_t__ codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ CinFileHeader ;
typedef  TYPE_3__ CinDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_DSICINAUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_DSICINVIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 
 int cin_read_file_header (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cin_read_header(AVFormatContext *s)
{
    int rc;
    CinDemuxContext *cin = s->priv_data;
    CinFileHeader *hdr = &cin->file_header;
    AVIOContext *pb = s->pb;
    AVStream *st;

    rc = cin_read_file_header(cin, pb);
    if (rc)
        return rc;

    cin->video_stream_pts = 0;
    cin->audio_stream_pts = 0;
    cin->audio_buffer_size = 0;

    /* initialize the video decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avpriv_set_pts_info(st, 32, 1, 12);
    cin->video_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_DSICINVIDEO;
    st->codecpar->codec_tag = 0;  /* no fourcc */
    st->codecpar->width = hdr->video_frame_width;
    st->codecpar->height = hdr->video_frame_height;

    /* initialize the audio decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avpriv_set_pts_info(st, 32, 1, 22050);
    cin->audio_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_DSICINAUDIO;
    st->codecpar->codec_tag = 0;  /* no tag */
    st->codecpar->channels = 1;
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    st->codecpar->sample_rate = 22050;
    st->codecpar->bits_per_coded_sample = 8;
    st->codecpar->bit_rate = st->codecpar->sample_rate * st->codecpar->bits_per_coded_sample * st->codecpar->channels;

    return 0;
}