#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {double duration; double field_duration; TYPE_4__* context; TYPE_1__* title; } ;
typedef  TYPE_5__ hb_work_private_t ;
struct TYPE_17__ {TYPE_2__* iformat; TYPE_6__** streams; } ;
struct TYPE_16__ {long long num; long long den; } ;
struct TYPE_15__ {TYPE_7__ time_base; TYPE_7__ avg_frame_rate; scalar_t__ nb_frames; scalar_t__ duration; } ;
struct TYPE_12__ {int num; int den; } ;
struct TYPE_13__ {int ticks_per_frame; TYPE_3__ time_base; } ;
struct TYPE_11__ {scalar_t__ raw_codec_id; } ;
struct TYPE_10__ {size_t video_id; scalar_t__ opaque_priv; } ;
typedef  TYPE_6__ AVStream ;
typedef  TYPE_7__ AVRational ;
typedef  TYPE_8__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 

__attribute__((used)) static void compute_frame_duration( hb_work_private_t *pv )
{
    double duration = 0.;
    int64_t max_fps = 64LL;

    // context->time_base may be in fields, so set the max *fields* per second
    if ( pv->context->ticks_per_frame > 1 )
        max_fps *= pv->context->ticks_per_frame;

    if ( pv->title->opaque_priv )
    {
        // If ffmpeg is demuxing for us, it collects some additional
        // information about framerates that is often more accurate
        // than context->time_base.
        AVFormatContext *ic = (AVFormatContext*)pv->title->opaque_priv;
        AVStream *st = ic->streams[pv->title->video_id];
        if ( st->nb_frames && st->duration )
        {
            // compute the average frame duration from the total number
            // of frames & the total duration.
            duration = ( (double)st->duration * (double)st->time_base.num ) /
                       ( (double)st->nb_frames * (double)st->time_base.den );
        }
        // Raw demuxers set a default fps of 25 and do not parse
        // a value from the container.  So use the codec time_base
        // for raw demuxers.
        else if (ic->iformat->raw_codec_id == AV_CODEC_ID_NONE)
        {
            // XXX We don't have a frame count or duration so try to use the
            // far less reliable time base info in the stream.
            // Because the time bases are so screwed up, we only take values
            // in the range 8fps - 64fps.
            AVRational *tb = NULL;
            if ( st->avg_frame_rate.den * 64LL > st->avg_frame_rate.num &&
                 st->avg_frame_rate.num > st->avg_frame_rate.den * 8LL )
            {
                tb = &(st->avg_frame_rate);
                duration =  (double)tb->den / (double)tb->num;
            }
            else if ( st->time_base.num * 64LL > st->time_base.den &&
                      st->time_base.den > st->time_base.num * 8LL )
            {
                tb = &(st->time_base);
                duration =  (double)tb->num / (double)tb->den;
            }
        }
        if ( !duration &&
             pv->context->time_base.num * max_fps > pv->context->time_base.den &&
             pv->context->time_base.den > pv->context->time_base.num * 8LL )
        {
            duration =  (double)pv->context->time_base.num /
                        (double)pv->context->time_base.den;
            if ( pv->context->ticks_per_frame > 1 )
            {
                // for ffmpeg 0.5 & later, the H.264 & MPEG-2 time base is
                // field rate rather than frame rate so convert back to frames.
                duration *= pv->context->ticks_per_frame;
            }
        }
    }
    else
    {
        if ( pv->context->time_base.num * max_fps > pv->context->time_base.den &&
             pv->context->time_base.den > pv->context->time_base.num * 8LL )
        {
            duration =  (double)pv->context->time_base.num /
                            (double)pv->context->time_base.den;
            if ( pv->context->ticks_per_frame > 1 )
            {
                // for ffmpeg 0.5 & later, the H.264 & MPEG-2 time base is
                // field rate rather than frame rate so convert back to frames.
                duration *= pv->context->ticks_per_frame;
            }
        }
    }
    if ( duration == 0 )
    {
        // No valid timing info found in the stream, so pick some value
        duration = 1001. / 24000.;
    }
    pv->duration = duration * 90000.;
    pv->field_duration = pv->duration;
    if ( pv->context->ticks_per_frame > 1 )
    {
        pv->field_duration /= pv->context->ticks_per_frame;
    }
}