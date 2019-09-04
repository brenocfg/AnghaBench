#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_ABGR 142 
#define  AV_PIX_FMT_ARGB 141 
#define  AV_PIX_FMT_BGR24 140 
#define  AV_PIX_FMT_BGR555BE 139 
#define  AV_PIX_FMT_BGR555LE 138 
#define  AV_PIX_FMT_BGR565BE 137 
#define  AV_PIX_FMT_BGR565LE 136 
#define  AV_PIX_FMT_BGRA 135 
#define  AV_PIX_FMT_NONE 134 
#define  AV_PIX_FMT_RGB24 133 
#define  AV_PIX_FMT_RGB555BE 132 
#define  AV_PIX_FMT_RGB555LE 131 
#define  AV_PIX_FMT_RGB565BE 130 
#define  AV_PIX_FMT_RGB565LE 129 
#define  AV_PIX_FMT_RGBA 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_RGBA, AV_PIX_FMT_BGRA, AV_PIX_FMT_ARGB, AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGB24, AV_PIX_FMT_BGR24,
        AV_PIX_FMT_RGB565BE, AV_PIX_FMT_BGR565BE, AV_PIX_FMT_RGB555BE, AV_PIX_FMT_BGR555BE,
        AV_PIX_FMT_RGB565LE, AV_PIX_FMT_BGR565LE, AV_PIX_FMT_RGB555LE, AV_PIX_FMT_BGR555LE,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}