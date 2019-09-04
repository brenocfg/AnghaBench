#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {TYPE_5__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {TYPE_1__* comp; } ;
struct TYPE_9__ {int max; int /*<<< orphan*/  do_lumakey_slice; scalar_t__ tolerance; scalar_t__ threshold; void* black; void* white; } ;
struct TYPE_8__ {int depth; } ;
typedef  TYPE_2__ LumakeyContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 void* av_clip (scalar_t__,int /*<<< orphan*/ ,int) ; 
 void* av_clip_uint8 (scalar_t__) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_lumakey_slice16 ; 
 int /*<<< orphan*/  do_lumakey_slice8 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    LumakeyContext *s = ctx->priv;
    int depth;

    depth = desc->comp[0].depth;
    if (depth == 8) {
        s->white = av_clip_uint8(s->threshold + s->tolerance);
        s->black = av_clip_uint8(s->threshold - s->tolerance);
        s->do_lumakey_slice = do_lumakey_slice8;
    } else {
        s->max = (1 << depth) - 1;
        s->white = av_clip(s->threshold + s->tolerance, 0, s->max);
        s->black = av_clip(s->threshold - s->tolerance, 0, s->max);
        s->do_lumakey_slice = do_lumakey_slice16;
    }

    return 0;
}