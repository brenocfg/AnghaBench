#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_2__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_10__ {int /*<<< orphan*/  video_stream_index; TYPE_1__ fps; } ;
struct TYPE_9__ {int extradata_size; void* height; void* width; int /*<<< orphan*/  extradata; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ FourxmDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_4XM ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 void* AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 TYPE_4__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtrk_SIZE ; 

__attribute__((used)) static int parse_vtrk(AVFormatContext *s,
                      FourxmDemuxContext *fourxm, uint8_t *buf, int size,
                      int left)
{
    AVStream *st;
    /* check that there is enough data */
    if (size != vtrk_SIZE || left < size + 8) {
        return AVERROR_INVALIDDATA;
    }

    /* allocate a new AVStream */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avpriv_set_pts_info(st, 60, fourxm->fps.den, fourxm->fps.num);

    fourxm->video_stream_index = st->index;

    st->codecpar->codec_type     = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id       = AV_CODEC_ID_4XM;

    st->codecpar->extradata      = av_mallocz(4 + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!st->codecpar->extradata)
        return AVERROR(ENOMEM);
    st->codecpar->extradata_size = 4;
    AV_WL32(st->codecpar->extradata, AV_RL32(buf + 16));
    st->codecpar->width  = AV_RL32(buf + 36);
    st->codecpar->height = AV_RL32(buf + 40);

    return 0;
}