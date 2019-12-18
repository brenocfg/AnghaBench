#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_6__ {scalar_t__ color_model; } ;
struct TYPE_7__ {TYPE_1__ plugin_info; } ;
typedef  TYPE_2__ Frei0rContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_ABGR 131 
#define  AV_PIX_FMT_ARGB 130 
#define  AV_PIX_FMT_BGRA 129 
#define  AV_PIX_FMT_NONE 128 
 int const AV_PIX_FMT_RGBA ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ F0R_COLOR_MODEL_BGRA8888 ; 
 scalar_t__ F0R_COLOR_MODEL_RGBA8888 ; 
 int ff_add_format (int /*<<< orphan*/ **,int const) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    Frei0rContext *s = ctx->priv;
    AVFilterFormats *formats = NULL;
    int ret;

    if        (s->plugin_info.color_model == F0R_COLOR_MODEL_BGRA8888) {
        if ((ret = ff_add_format(&formats, AV_PIX_FMT_BGRA)) < 0)
            return ret;
    } else if (s->plugin_info.color_model == F0R_COLOR_MODEL_RGBA8888) {
        if ((ret = ff_add_format(&formats, AV_PIX_FMT_RGBA)) < 0)
            return ret;
    } else {                                   /* F0R_COLOR_MODEL_PACKED32 */
        static const enum AVPixelFormat pix_fmts[] = {
            AV_PIX_FMT_BGRA, AV_PIX_FMT_ARGB, AV_PIX_FMT_ABGR, AV_PIX_FMT_ARGB, AV_PIX_FMT_NONE
        };
        formats = ff_make_format_list(pix_fmts);
    }

    if (!formats)
        return AVERROR(ENOMEM);

    return ff_set_common_formats(ctx, formats);
}