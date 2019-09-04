#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_12__ {TYPE_2__** outputs; TYPE_1__** inputs; } ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  log2_chroma_h; scalar_t__ nb_components; } ;
struct TYPE_10__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_9__ {int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int av_pix_fmt_desc_get_id (TYPE_3__ const*) ; 
 TYPE_3__* av_pix_fmt_desc_next (TYPE_3__ const*) ; 
 int ff_add_format (int /*<<< orphan*/ **,int) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats  *formats;
    enum AVPixelFormat pix_fmt;
    int              ret;

    /** accept any input pixel format that is not hardware accelerated, not
     *  a bitstream format, and does not have vertically sub-sampled chroma */
    if (ctx->inputs[0]) {
        const AVPixFmtDescriptor *desc = NULL;
        formats = NULL;
        while ((desc = av_pix_fmt_desc_next(desc))) {
            pix_fmt = av_pix_fmt_desc_get_id(desc);
            if (!(desc->flags & AV_PIX_FMT_FLAG_HWACCEL ||
                  desc->flags & AV_PIX_FMT_FLAG_PAL     ||
                  desc->flags & AV_PIX_FMT_FLAG_BITSTREAM) &&
                desc->nb_components && !desc->log2_chroma_h &&
                (ret = ff_add_format(&formats, pix_fmt)) < 0)
                return ret;
        }
        if ((ret = ff_formats_ref(formats, &ctx->inputs[0]->out_formats)) < 0 ||
            (ret = ff_formats_ref(formats, &ctx->outputs[0]->in_formats)) < 0)
            return ret;
    }

    return 0;
}