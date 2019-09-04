#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_15__ {int num; int den; } ;
struct TYPE_14__ {int audio_preload; TYPE_2__** streams; } ;
struct TYPE_13__ {size_t stream_index; int dts; } ;
struct TYPE_12__ {TYPE_8__ time_base; TYPE_1__* codecpar; } ;
struct TYPE_11__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int av_compare_ts (int,TYPE_8__,int,TYPE_8__) ; 
 int av_rescale_q (int,TYPE_8__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interleave_compare_dts(AVFormatContext *s, AVPacket *next,
                                  AVPacket *pkt)
{
    AVStream *st  = s->streams[pkt->stream_index];
    AVStream *st2 = s->streams[next->stream_index];
    int comp      = av_compare_ts(next->dts, st2->time_base, pkt->dts,
                                  st->time_base);
    if (s->audio_preload && ((st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) != (st2->codecpar->codec_type == AVMEDIA_TYPE_AUDIO))) {
        int64_t ts = av_rescale_q(pkt ->dts, st ->time_base, AV_TIME_BASE_Q) - s->audio_preload*(st ->codecpar->codec_type == AVMEDIA_TYPE_AUDIO);
        int64_t ts2= av_rescale_q(next->dts, st2->time_base, AV_TIME_BASE_Q) - s->audio_preload*(st2->codecpar->codec_type == AVMEDIA_TYPE_AUDIO);
        if (ts == ts2) {
            ts= ( pkt ->dts* st->time_base.num*AV_TIME_BASE - s->audio_preload*(int64_t)(st ->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)* st->time_base.den)*st2->time_base.den
               -( next->dts*st2->time_base.num*AV_TIME_BASE - s->audio_preload*(int64_t)(st2->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)*st2->time_base.den)* st->time_base.den;
            ts2=0;
        }
        comp= (ts>ts2) - (ts<ts2);
    }

    if (comp == 0)
        return pkt->stream_index < next->stream_index;
    return comp > 0;
}