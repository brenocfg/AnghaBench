#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_14__ {TYPE_2__* priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  format; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_12__ {int flags; int nb_components; TYPE_1__* comp; } ;
struct TYPE_11__ {int requested_planes; int depth; int step; int is_packed; size_t* map; int /*<<< orphan*/  linesize; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_2__ ExtractPlanesContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_ALPHA ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  EINVAL ; 
 int PLANE_A ; 
 int PLANE_B ; 
 int PLANE_G ; 
 int PLANE_R ; 
 int PLANE_U ; 
 int PLANE_V ; 
 int PLANE_Y ; 
 int av_get_padded_bits_per_pixel (TYPE_3__ const*) ; 
 int av_image_fill_linesizes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ExtractPlanesContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int plane_avail, ret, i;
    uint8_t rgba_map[4];

    plane_avail = ((desc->flags & AV_PIX_FMT_FLAG_RGB) ? PLANE_R|PLANE_G|PLANE_B :
                                                 PLANE_Y |
                                ((desc->nb_components > 2) ? PLANE_U|PLANE_V : 0)) |
                  ((desc->flags & AV_PIX_FMT_FLAG_ALPHA) ? PLANE_A : 0);
    if (s->requested_planes & ~plane_avail) {
        av_log(ctx, AV_LOG_ERROR, "Requested planes not available.\n");
        return AVERROR(EINVAL);
    }
    if ((ret = av_image_fill_linesizes(s->linesize, inlink->format, inlink->w)) < 0)
        return ret;

    s->depth = desc->comp[0].depth >> 3;
    s->step = av_get_padded_bits_per_pixel(desc) >> 3;
    s->is_packed = !(desc->flags & AV_PIX_FMT_FLAG_PLANAR) &&
                    (desc->nb_components > 1);
    if (desc->flags & AV_PIX_FMT_FLAG_RGB) {
        ff_fill_rgba_map(rgba_map, inlink->format);
        for (i = 0; i < 4; i++)
            s->map[i] = rgba_map[s->map[i]];
    }

    return 0;
}