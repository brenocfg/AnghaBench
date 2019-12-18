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
typedef  int /*<<< orphan*/  FFDrawContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;

/* Variables and functions */
 scalar_t__ av_pix_fmt_desc_get (int) ; 
 int ff_add_format (int /*<<< orphan*/ **,int) ; 
 scalar_t__ ff_draw_init (int /*<<< orphan*/ *,int,unsigned int) ; 

AVFilterFormats *ff_draw_supported_pixel_formats(unsigned flags)
{
    enum AVPixelFormat i;
    FFDrawContext draw;
    AVFilterFormats *fmts = NULL;
    int ret;

    for (i = 0; av_pix_fmt_desc_get(i); i++)
        if (ff_draw_init(&draw, i, flags) >= 0 &&
            (ret = ff_add_format(&fmts, i)) < 0)
            return NULL;
    return fmts;
}