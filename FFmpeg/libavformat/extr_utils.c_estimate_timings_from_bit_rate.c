#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int bit_rate; int nb_streams; scalar_t__ duration; TYPE_6__** streams; TYPE_4__* internal; scalar_t__ pb; } ;
struct TYPE_14__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_15__ {int codec_info_nb_frames; scalar_t__ duration; TYPE_5__ time_base; TYPE_3__* codecpar; TYPE_2__* internal; } ;
struct TYPE_13__ {scalar_t__ data_offset; } ;
struct TYPE_12__ {scalar_t__ bit_rate; scalar_t__ codec_type; } ;
struct TYPE_11__ {TYPE_1__* avctx; } ;
struct TYPE_10__ {scalar_t__ bit_rate; } ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int INT64_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_rescale (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ avio_size (scalar_t__) ; 

__attribute__((used)) static void estimate_timings_from_bit_rate(AVFormatContext *ic)
{
    int64_t filesize, duration;
    int i, show_warning = 0;
    AVStream *st;

    /* if bit_rate is already set, we believe it */
    if (ic->bit_rate <= 0) {
        int64_t bit_rate = 0;
        for (i = 0; i < ic->nb_streams; i++) {
            st = ic->streams[i];
            if (st->codecpar->bit_rate <= 0 && st->internal->avctx->bit_rate > 0)
                st->codecpar->bit_rate = st->internal->avctx->bit_rate;
            if (st->codecpar->bit_rate > 0) {
                if (INT64_MAX - st->codecpar->bit_rate < bit_rate) {
                    bit_rate = 0;
                    break;
                }
                bit_rate += st->codecpar->bit_rate;
            } else if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && st->codec_info_nb_frames > 1) {
                // If we have a videostream with packets but without a bitrate
                // then consider the sum not known
                bit_rate = 0;
                break;
            }
        }
        ic->bit_rate = bit_rate;
    }

    /* if duration is already set, we believe it */
    if (ic->duration == AV_NOPTS_VALUE &&
        ic->bit_rate != 0) {
        filesize = ic->pb ? avio_size(ic->pb) : 0;
        if (filesize > ic->internal->data_offset) {
            filesize -= ic->internal->data_offset;
            for (i = 0; i < ic->nb_streams; i++) {
                st      = ic->streams[i];
                if (   st->time_base.num <= INT64_MAX / ic->bit_rate
                    && st->duration == AV_NOPTS_VALUE) {
                    duration = av_rescale(8 * filesize, st->time_base.den,
                                          ic->bit_rate *
                                          (int64_t) st->time_base.num);
                    st->duration = duration;
                    show_warning = 1;
                }
            }
        }
    }
    if (show_warning)
        av_log(ic, AV_LOG_WARNING,
               "Estimating duration from bitrate, this may be inaccurate\n");
}