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
struct TYPE_16__ {int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_15__ {int /*<<< orphan*/  nb_components; TYPE_2__* comp; } ;
struct TYPE_14__ {int history_len; int smoothing; int /*<<< orphan*/ * history_mem; TYPE_4__* max; TYPE_3__* min; int /*<<< orphan*/  num_components; int /*<<< orphan*/ * co; } ;
struct TYPE_13__ {int /*<<< orphan*/ * history; } ;
struct TYPE_12__ {int /*<<< orphan*/ * history; } ;
struct TYPE_11__ {int /*<<< orphan*/  offset; } ;
struct TYPE_10__ {TYPE_5__* priv; } ;
typedef  TYPE_5__ NormalizeContext ;
typedef  TYPE_6__ AVPixFmtDescriptor ;
typedef  TYPE_7__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 TYPE_6__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    NormalizeContext *s = inlink->dst->priv;
    // Store offsets to R,G,B,A bytes respectively in each pixel
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int c;

    for (c = 0; c < 4; ++c)
        s->co[c] = desc->comp[c].offset;
    s->num_components = desc->nb_components;
    // Convert smoothing value to history_len (a count of frames to average,
    // must be at least 1).  Currently this is a direct assignment, but the
    // smoothing value was originally envisaged as a number of seconds.  In
    // future it would be nice to set history_len using a number of seconds,
    // but VFR video is currently an obstacle to doing so.
    s->history_len = s->smoothing + 1;
    // Allocate the history buffers -- there are 6 -- one for each extrema.
    // s->smoothing is limited to INT_MAX/8, so that (s->history_len * 6)
    // can't overflow on 32bit causing a too-small allocation.
    s->history_mem = av_malloc(s->history_len * 6);
    if (s->history_mem == NULL)
        return AVERROR(ENOMEM);

    for (c = 0; c < 3; c++) {
        s->min[c].history = s->history_mem + (c*2)   * s->history_len;
        s->max[c].history = s->history_mem + (c*2+1) * s->history_len;
    }
    return 0;
}