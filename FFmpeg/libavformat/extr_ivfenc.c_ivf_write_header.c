#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ codec_type; scalar_t__ codec_id; int width; int height; } ;
struct TYPE_9__ {int nb_streams; TYPE_2__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_8__ {TYPE_1__ time_base; TYPE_4__* codecpar; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_AV1 ; 
 scalar_t__ AV_CODEC_ID_VP8 ; 
 scalar_t__ AV_CODEC_ID_VP9 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RL32 (char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int ivf_write_header(AVFormatContext *s)
{
    AVCodecParameters *par;
    AVIOContext *pb = s->pb;

    if (s->nb_streams != 1) {
        av_log(s, AV_LOG_ERROR, "Format supports only exactly one video stream\n");
        return AVERROR(EINVAL);
    }
    par = s->streams[0]->codecpar;
    if (par->codec_type != AVMEDIA_TYPE_VIDEO ||
        !(par->codec_id == AV_CODEC_ID_AV1 ||
          par->codec_id == AV_CODEC_ID_VP8 ||
          par->codec_id == AV_CODEC_ID_VP9)) {
        av_log(s, AV_LOG_ERROR, "Currently only VP8, VP9 and AV1 are supported!\n");
        return AVERROR(EINVAL);
    }
    avio_write(pb, "DKIF", 4);
    avio_wl16(pb, 0); // version
    avio_wl16(pb, 32); // header length
    avio_wl32(pb,
              par->codec_id == AV_CODEC_ID_VP9 ? AV_RL32("VP90") :
              par->codec_id == AV_CODEC_ID_VP8 ? AV_RL32("VP80") : AV_RL32("AV01"));
    avio_wl16(pb, par->width);
    avio_wl16(pb, par->height);
    avio_wl32(pb, s->streams[0]->time_base.den);
    avio_wl32(pb, s->streams[0]->time_base.num);
    avio_wl64(pb, 0xFFFFFFFFFFFFFFFFULL); // length is overwritten at the end of muxing

    return 0;
}