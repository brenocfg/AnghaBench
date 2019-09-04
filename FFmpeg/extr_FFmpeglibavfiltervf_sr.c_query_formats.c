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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int const AV_PIX_FMT_GRAY8 ; 
 int const AV_PIX_FMT_NONE ; 
 int const AV_PIX_FMT_YUV410P ; 
 int const AV_PIX_FMT_YUV411P ; 
 int const AV_PIX_FMT_YUV420P ; 
 int const AV_PIX_FMT_YUV422P ; 
 int const AV_PIX_FMT_YUV444P ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *context)
{
    const enum AVPixelFormat pixel_formats[] = {AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUV444P,
                                                AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV411P, AV_PIX_FMT_GRAY8,
                                                AV_PIX_FMT_NONE};
    AVFilterFormats *formats_list;

    formats_list = ff_make_format_list(pixel_formats);
    if (!formats_list){
        av_log(context, AV_LOG_ERROR, "could not create formats list\n");
        return AVERROR(ENOMEM);
    }

    return ff_set_common_formats(context, formats_list);
}