#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int codec_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_13__ {TYPE_3__* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  time_base; TYPE_5__* src; } ;
struct TYPE_11__ {TYPE_2__* st; } ;
struct TYPE_10__ {TYPE_1__* st; } ;
struct TYPE_9__ {int /*<<< orphan*/  r_frame_rate; int /*<<< orphan*/  time_base; TYPE_6__* codecpar; } ;
typedef  TYPE_2__ MovieStream ;
typedef  TYPE_3__ MovieContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 unsigned int FF_OUTLINK_IDX (TYPE_4__*) ; 

__attribute__((used)) static int movie_config_output_props(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    MovieContext *movie  = ctx->priv;
    unsigned out_id = FF_OUTLINK_IDX(outlink);
    MovieStream *st = &movie->st[out_id];
    AVCodecParameters *c = st->st->codecpar;

    outlink->time_base = st->st->time_base;

    switch (c->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        outlink->w          = c->width;
        outlink->h          = c->height;
        outlink->frame_rate = st->st->r_frame_rate;
        break;
    case AVMEDIA_TYPE_AUDIO:
        break;
    }

    return 0;
}