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
struct TYPE_17__ {TYPE_5__** outputs; TYPE_4__** inputs; TYPE_6__* priv; } ;
struct TYPE_16__ {int flags; scalar_t__ nb_components; TYPE_2__* comp; } ;
struct TYPE_15__ {int out_fmt; int nb_inputs; TYPE_3__* outdesc; } ;
struct TYPE_14__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_13__ {int /*<<< orphan*/  out_formats; } ;
struct TYPE_12__ {int flags; TYPE_1__* comp; } ;
struct TYPE_11__ {int depth; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_6__ MergePlanesContext ;
typedef  TYPE_7__ AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_BE ; 
 scalar_t__ av_pix_fmt_count_planes (int) ; 
 void* av_pix_fmt_desc_get (int) ; 
 int ff_add_format (int /*<<< orphan*/ **,int) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    MergePlanesContext *s = ctx->priv;
    AVFilterFormats *formats = NULL;
    int i, ret;

    s->outdesc = av_pix_fmt_desc_get(s->out_fmt);
    for (i = 0; av_pix_fmt_desc_get(i); i++) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(i);
        if (desc->comp[0].depth == s->outdesc->comp[0].depth &&
            (desc->comp[0].depth <= 8 || (desc->flags & AV_PIX_FMT_FLAG_BE) == (s->outdesc->flags & AV_PIX_FMT_FLAG_BE)) &&
            av_pix_fmt_count_planes(i) == desc->nb_components &&
            (ret = ff_add_format(&formats, i)) < 0)
                return ret;
    }

    for (i = 0; i < s->nb_inputs; i++)
        if ((ret = ff_formats_ref(formats, &ctx->inputs[i]->out_formats)) < 0)
            return ret;

    formats = NULL;
    if ((ret = ff_add_format(&formats, s->out_fmt)) < 0 ||
        (ret = ff_formats_ref(formats, &ctx->outputs[0]->in_formats)) < 0)
        return ret;

    return 0;
}