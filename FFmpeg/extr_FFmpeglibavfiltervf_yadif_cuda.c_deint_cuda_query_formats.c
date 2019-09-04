#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_7__ {TYPE_2__** outputs; TYPE_1__** inputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_5__ {int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_CUDA ; 
 int AV_PIX_FMT_NONE ; 
 int ff_formats_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_make_format_list (int*) ; 

__attribute__((used)) static int deint_cuda_query_formats(AVFilterContext *ctx)
{
    enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_CUDA, AV_PIX_FMT_NONE,
    };
    int ret;

    if ((ret = ff_formats_ref(ff_make_format_list(pix_fmts),
                              &ctx->inputs[0]->out_formats)) < 0)
        return ret;
    if ((ret = ff_formats_ref(ff_make_format_list(pix_fmts),
                              &ctx->outputs[0]->in_formats)) < 0)
        return ret;

    return 0;
}