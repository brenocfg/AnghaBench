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
struct ogg_stream {scalar_t__ lastpts; scalar_t__ lastdts; long long granule; TYPE_1__* codec; scalar_t__ page_end; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {struct ogg* priv_data; } ;
struct TYPE_5__ {scalar_t__ granule_is_start; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 void* ogg_gptopts (TYPE_2__*,int,long long,scalar_t__*) ; 

__attribute__((used)) static int64_t ogg_calc_pts(AVFormatContext *s, int idx, int64_t *dts)
{
    struct ogg *ogg       = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    int64_t pts           = AV_NOPTS_VALUE;

    if (dts)
        *dts = AV_NOPTS_VALUE;

    if (os->lastpts != AV_NOPTS_VALUE) {
        pts         = os->lastpts;
        os->lastpts = AV_NOPTS_VALUE;
    }
    if (os->lastdts != AV_NOPTS_VALUE) {
        if (dts)
            *dts = os->lastdts;
        os->lastdts = AV_NOPTS_VALUE;
    }
    if (os->page_end) {
        if (os->granule != -1LL) {
            if (os->codec && os->codec->granule_is_start)
                pts = ogg_gptopts(s, idx, os->granule, dts);
            else
                os->lastpts = ogg_gptopts(s, idx, os->granule, &os->lastdts);
            os->granule = -1LL;
        }
    }
    return pts;
}