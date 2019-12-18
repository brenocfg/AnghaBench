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
#define  AV_PIX_FMT_0BGR 142 
#define  AV_PIX_FMT_0RGB 141 
#define  AV_PIX_FMT_ABGR 140 
#define  AV_PIX_FMT_ARGB 139 
#define  AV_PIX_FMT_BGR0 138 
#define  AV_PIX_FMT_BGR24 137 
#define  AV_PIX_FMT_BGR48 136 
#define  AV_PIX_FMT_BGRA 135 
#define  AV_PIX_FMT_BGRA64 134 
#define  AV_PIX_FMT_NONE 133 
#define  AV_PIX_FMT_RGB0 132 
#define  AV_PIX_FMT_RGB24 131 
#define  AV_PIX_FMT_RGB48 130 
#define  AV_PIX_FMT_RGBA 129 
#define  AV_PIX_FMT_RGBA64 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_0RGB,  AV_PIX_FMT_0BGR,
        AV_PIX_FMT_ARGB,  AV_PIX_FMT_ABGR,
        AV_PIX_FMT_RGB0,  AV_PIX_FMT_BGR0,
        AV_PIX_FMT_RGB24, AV_PIX_FMT_BGR24,
        AV_PIX_FMT_RGB48, AV_PIX_FMT_BGR48,
        AV_PIX_FMT_RGBA64, AV_PIX_FMT_BGRA64,
        AV_PIX_FMT_RGBA,  AV_PIX_FMT_BGRA,
        AV_PIX_FMT_NONE
    };

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, fmts_list);
}