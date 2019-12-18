#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {TYPE_5__** streams; TYPE_4__* priv_data; } ;
struct TYPE_16__ {size_t stream_index; int dts; } ;
struct TYPE_15__ {TYPE_1__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_12__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_14__ {TYPE_2__ time_base; } ;
struct TYPE_13__ {scalar_t__ order; } ;
struct TYPE_11__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ GXFStreamContext ;
typedef  TYPE_4__ GXFContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int av_rescale_rnd (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_compare_field_nb(AVFormatContext *s, const AVPacket *next,
                                                    const AVPacket *cur)
{
    GXFContext *gxf = s->priv_data;
    const AVPacket *pkt[2] = { cur, next };
    int i, field_nb[2];
    GXFStreamContext *sc[2];

    for (i = 0; i < 2; i++) {
        AVStream *st = s->streams[pkt[i]->stream_index];
        sc[i] = st->priv_data;
        if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            field_nb[i] = av_rescale_rnd(pkt[i]->dts, gxf->time_base.den,
                                         (int64_t)48000*gxf->time_base.num, AV_ROUND_UP);
            field_nb[i] &= ~1; // compare against even field number because audio must be before video
        } else
            field_nb[i] = pkt[i]->dts; // dts are field based
    }

    return field_nb[1] > field_nb[0] ||
        (field_nb[1] == field_nb[0] && sc[1]->order > sc[0]->order);
}