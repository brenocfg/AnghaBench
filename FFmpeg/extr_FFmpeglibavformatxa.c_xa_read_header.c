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
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_11__ {scalar_t__ start_time; TYPE_1__* codecpar; } ;
struct TYPE_10__ {void* out_size; } ;
struct TYPE_9__ {long long channels; long long sample_rate; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ MaxisXADemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_EA_MAXIS_XA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_clip (long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 long long avio_rl16 (int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,long long) ; 

__attribute__((used)) static int xa_read_header(AVFormatContext *s)
{
    MaxisXADemuxContext *xa = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;

    /*Set up the XA Audio Decoder*/
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type   = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id     = AV_CODEC_ID_ADPCM_EA_MAXIS_XA;
    avio_skip(pb, 4);       /* Skip the XA ID */
    xa->out_size            =  avio_rl32(pb);
    avio_skip(pb, 2);       /* Skip the tag */
    st->codecpar->channels     = avio_rl16(pb);
    st->codecpar->sample_rate  = avio_rl32(pb);
    avio_skip(pb, 4);       /* Skip average byte rate */
    avio_skip(pb, 2);       /* Skip block align */
    avio_skip(pb, 2);       /* Skip bits-per-sample */

    if (!st->codecpar->channels || !st->codecpar->sample_rate)
        return AVERROR_INVALIDDATA;

    st->codecpar->bit_rate = av_clip(15LL * st->codecpar->channels * 8 *
                                  st->codecpar->sample_rate / 28, 0, INT_MAX);

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
    st->start_time = 0;

    return 0;
}