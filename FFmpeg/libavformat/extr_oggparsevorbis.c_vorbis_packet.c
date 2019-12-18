#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct oggvorbis_private {int final_pts; int final_duration; int /*<<< orphan*/  vp; } ;
struct ogg_stream {void* lastpts; int flags; int granule; int pstart; int segp; int psize; int nsegs; int* segments; int lastdts; int pduration; int /*<<< orphan*/  pflags; int /*<<< orphan*/ * buf; struct oggvorbis_private* private; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {TYPE_1__** streams; struct ogg* priv_data; } ;
struct TYPE_5__ {void* start_time; void* duration; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 void* FFMAX (int,int /*<<< orphan*/ ) ; 
 int OGG_FLAG_EOS ; 
 int VORBIS_FLAG_COMMENT ; 
 int av_vorbis_parse_frame_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  av_vorbis_parse_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_update_metadata (TYPE_2__*,int) ; 

__attribute__((used)) static int vorbis_packet(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    struct oggvorbis_private *priv = os->private;
    int duration, flags = 0;

    if (!priv->vp)
        return AVERROR_INVALIDDATA;

    /* first packet handling
     * here we parse the duration of each packet in the first page and compare
     * the total duration to the page granule to find the encoder delay and
     * set the first timestamp */
    if ((!os->lastpts || os->lastpts == AV_NOPTS_VALUE) && !(os->flags & OGG_FLAG_EOS) && (int64_t)os->granule>=0) {
        int seg, d;
        uint8_t *last_pkt  = os->buf + os->pstart;
        uint8_t *next_pkt  = last_pkt;

        av_vorbis_parse_reset(priv->vp);
        duration = 0;
        seg = os->segp;
        d = av_vorbis_parse_frame_flags(priv->vp, last_pkt, 1, &flags);
        if (d < 0) {
            os->pflags |= AV_PKT_FLAG_CORRUPT;
            return 0;
        } else if (flags & VORBIS_FLAG_COMMENT) {
            vorbis_update_metadata(s, idx);
            flags = 0;
        }
        duration += d;
        last_pkt = next_pkt =  next_pkt + os->psize;
        for (; seg < os->nsegs; seg++) {
            if (os->segments[seg] < 255) {
                int d = av_vorbis_parse_frame_flags(priv->vp, last_pkt, 1, &flags);
                if (d < 0) {
                    duration = os->granule;
                    break;
                } else if (flags & VORBIS_FLAG_COMMENT) {
                    vorbis_update_metadata(s, idx);
                    flags = 0;
                }
                duration += d;
                last_pkt  = next_pkt + os->segments[seg];
            }
            next_pkt += os->segments[seg];
        }
        os->lastpts                 =
        os->lastdts                 = os->granule - duration;

        if (!os->granule && duration) //hack to deal with broken files (Ticket3710)
            os->lastpts = os->lastdts = AV_NOPTS_VALUE;

        if (s->streams[idx]->start_time == AV_NOPTS_VALUE) {
            s->streams[idx]->start_time = FFMAX(os->lastpts, 0);
            if (s->streams[idx]->duration != AV_NOPTS_VALUE)
                s->streams[idx]->duration -= s->streams[idx]->start_time;
        }
        priv->final_pts          = AV_NOPTS_VALUE;
        av_vorbis_parse_reset(priv->vp);
    }

    /* parse packet duration */
    if (os->psize > 0) {
        duration = av_vorbis_parse_frame_flags(priv->vp, os->buf + os->pstart, 1, &flags);
        if (duration < 0) {
            os->pflags |= AV_PKT_FLAG_CORRUPT;
            return 0;
        } else if (flags & VORBIS_FLAG_COMMENT) {
            vorbis_update_metadata(s, idx);
            flags = 0;
        }
        os->pduration = duration;
    }

    /* final packet handling
     * here we save the pts of the first packet in the final page, sum up all
     * packet durations in the final page except for the last one, and compare
     * to the page granule to find the duration of the final packet */
    if (os->flags & OGG_FLAG_EOS) {
        if (os->lastpts != AV_NOPTS_VALUE) {
            priv->final_pts      = os->lastpts;
            priv->final_duration = 0;
        }
        if (os->segp == os->nsegs)
            os->pduration = os->granule - priv->final_pts - priv->final_duration;
        priv->final_duration += os->pduration;
    }

    return 0;
}