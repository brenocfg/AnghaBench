#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {TYPE_1__** outputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  in_formats; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
#define  AV_PIX_FMT_NONE 129 
#define  AV_PIX_FMT_RGBA 128 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterLink *outlink = ctx->outputs[0];
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_RGBA,
        AV_PIX_FMT_NONE
    };
    int ret;

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if ((ret = ff_formats_ref(fmts_list, &outlink->in_formats)) < 0)
        return ret;

    return 0;
}