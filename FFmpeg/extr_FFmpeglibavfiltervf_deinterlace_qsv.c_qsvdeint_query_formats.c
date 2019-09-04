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
#define  AV_PIX_FMT_NONE 129 
#define  AV_PIX_FMT_QSV 128 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qsvdeint_query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pixel_formats[] = {
        AV_PIX_FMT_QSV, AV_PIX_FMT_NONE,
    };
    AVFilterFormats *pix_fmts  = ff_make_format_list(pixel_formats);
    int ret;

    if ((ret = ff_set_common_formats(ctx, pix_fmts)) < 0)
        return ret;

    return 0;
}