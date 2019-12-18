#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int height; int width; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_10__ {int duration; TYPE_5__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_WMV3 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  VC1_EXTRADATA_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rl24 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 scalar_t__ ff_get_extradata (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc1t_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream *st;
    int frames;
    uint32_t fps;
    uint32_t size;

    frames = avio_rl24(pb);
    if (avio_r8(pb) != 0xC5 || ((size = avio_rl32(pb)) < 4))
        return AVERROR_INVALIDDATA;

    /* init video codec */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_WMV3;

    if (ff_get_extradata(s, st->codecpar, pb, VC1_EXTRADATA_SIZE) < 0)
        return AVERROR(ENOMEM);

    avio_skip(pb, size - 4);
    st->codecpar->height = avio_rl32(pb);
    st->codecpar->width = avio_rl32(pb);
    if(avio_rl32(pb) != 0xC)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 8);
    fps = avio_rl32(pb);
    if(fps == 0xFFFFFFFF)
        avpriv_set_pts_info(st, 32, 1, 1000);
    else{
        if (!fps) {
            av_log(s, AV_LOG_ERROR, "Zero FPS specified, defaulting to 1 FPS\n");
            fps = 1;
        }
        avpriv_set_pts_info(st, 24, 1, fps);
        st->duration = frames;
    }

    return 0;
}