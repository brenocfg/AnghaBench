#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv_data; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {scalar_t__ cache_size; int /*<<< orphan*/  dts; scalar_t__ buffer_size; scalar_t__ buffer; scalar_t__ buffer_ptr; scalar_t__ soi_ptr; } ;
struct TYPE_9__ {int channels; int sample_rate; int bits_per_coded_sample; int block_align; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ MXGContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MXPEG ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_ALAW ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int mxg_read_header(AVFormatContext *s)
{
    AVStream *video_st, *audio_st;
    MXGContext *mxg = s->priv_data;

    /* video parameters will be extracted from the compressed bitstream */
    video_st = avformat_new_stream(s, NULL);
    if (!video_st)
        return AVERROR(ENOMEM);
    video_st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    video_st->codecpar->codec_id = AV_CODEC_ID_MXPEG;
    avpriv_set_pts_info(video_st, 64, 1, 1000000);

    audio_st = avformat_new_stream(s, NULL);
    if (!audio_st)
        return AVERROR(ENOMEM);
    audio_st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    audio_st->codecpar->codec_id = AV_CODEC_ID_PCM_ALAW;
    audio_st->codecpar->channels = 1;
    audio_st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    audio_st->codecpar->sample_rate = 8000;
    audio_st->codecpar->bits_per_coded_sample = 8;
    audio_st->codecpar->block_align = 1;
    avpriv_set_pts_info(audio_st, 64, 1, 1000000);

    mxg->soi_ptr = mxg->buffer_ptr = mxg->buffer = 0;
    mxg->buffer_size = 0;
    mxg->dts = AV_NOPTS_VALUE;
    mxg->cache_size = 0;

    return 0;
}