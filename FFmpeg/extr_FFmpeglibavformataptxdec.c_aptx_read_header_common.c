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
struct TYPE_11__ {scalar_t__ start_time; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_rate; } ;
struct TYPE_9__ {int channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AptXDemuxerContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32P ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static AVStream *aptx_read_header_common(AVFormatContext *s)
{
    AptXDemuxerContext *s1 = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return NULL;
    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->format = AV_SAMPLE_FMT_S32P;
    st->codecpar->channels = 2;
    st->codecpar->sample_rate = s1->sample_rate;
    st->start_time = 0;
    return st;
}