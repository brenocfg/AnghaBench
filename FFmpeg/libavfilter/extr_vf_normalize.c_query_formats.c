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
#define  AV_PIX_FMT_0BGR 138 
#define  AV_PIX_FMT_0RGB 137 
#define  AV_PIX_FMT_ABGR 136 
#define  AV_PIX_FMT_ARGB 135 
#define  AV_PIX_FMT_BGR0 134 
#define  AV_PIX_FMT_BGR24 133 
#define  AV_PIX_FMT_BGRA 132 
#define  AV_PIX_FMT_NONE 131 
#define  AV_PIX_FMT_RGB0 130 
#define  AV_PIX_FMT_RGB24 129 
#define  AV_PIX_FMT_RGBA 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pixel_fmts[] = {
        AV_PIX_FMT_RGB24,
        AV_PIX_FMT_BGR24,
        AV_PIX_FMT_ARGB,
        AV_PIX_FMT_RGBA,
        AV_PIX_FMT_ABGR,
        AV_PIX_FMT_BGRA,
        AV_PIX_FMT_0RGB,
        AV_PIX_FMT_RGB0,
        AV_PIX_FMT_0BGR,
        AV_PIX_FMT_BGR0,
        AV_PIX_FMT_NONE
    };
    // According to filter_design.txt, using ff_set_common_formats() this way
    // ensures the pixel formats of the input and output will be the same. That
    // saves a bit of effort possibly needing to handle format conversions.
    AVFilterFormats *formats = ff_make_format_list(pixel_fmts);
    if (!formats)
        return AVERROR(ENOMEM);
    return ff_set_common_formats(ctx, formats);
}