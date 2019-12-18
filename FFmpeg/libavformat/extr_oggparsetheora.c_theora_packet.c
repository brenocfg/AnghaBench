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
struct ogg_stream {scalar_t__ lastpts; int flags; int segp; int nsegs; int* segments; scalar_t__ lastdts; scalar_t__ psize; int pduration; int /*<<< orphan*/  granule; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {TYPE_1__** streams; struct ogg* priv_data; } ;
struct TYPE_5__ {scalar_t__ start_time; scalar_t__ duration; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int OGG_FLAG_EOS ; 
 scalar_t__ theora_gptopts (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int theora_packet(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    int duration;

    /* first packet handling
       here we parse the duration of each packet in the first page and compare
       the total duration to the page granule to find the encoder delay and
       set the first timestamp */

    if ((!os->lastpts || os->lastpts == AV_NOPTS_VALUE) && !(os->flags & OGG_FLAG_EOS)) {
        int seg;
        int64_t pts;

        duration = 1;
        for (seg = os->segp; seg < os->nsegs; seg++) {
            if (os->segments[seg] < 255)
                duration ++;
        }

        pts = theora_gptopts(s, idx, os->granule, NULL);
        if (pts != AV_NOPTS_VALUE)
            pts -= duration;
        os->lastpts = os->lastdts = pts;
        if(s->streams[idx]->start_time == AV_NOPTS_VALUE) {
            s->streams[idx]->start_time = os->lastpts;
            if (s->streams[idx]->duration > 0)
                s->streams[idx]->duration -= s->streams[idx]->start_time;
        }
    }

    /* parse packet duration */
    if (os->psize > 0) {
        os->pduration = 1;
    }

    return 0;
}