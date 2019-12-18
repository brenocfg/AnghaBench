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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int fmt; } ;
typedef  TYPE_1__ DnnProcessingContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/ * ff_make_format_list (int*) ; 
 int ff_set_common_formats (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *context)
{
    AVFilterFormats *formats;
    DnnProcessingContext *ctx = context->priv;
    enum AVPixelFormat pixel_fmts[2];
    pixel_fmts[0] = ctx->fmt;
    pixel_fmts[1] = AV_PIX_FMT_NONE;

    formats = ff_make_format_list(pixel_fmts);
    return ff_set_common_formats(context, formats);
}