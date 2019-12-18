#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int pix_fmt; int full_range; int /*<<< orphan*/  cv_fmt; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* cv_pix_fmts ; 

uint32_t av_map_videotoolbox_format_from_pixfmt2(enum AVPixelFormat pix_fmt, bool full_range)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        if (cv_pix_fmts[i].pix_fmt == pix_fmt && cv_pix_fmts[i].full_range == full_range)
            return cv_pix_fmts[i].cv_fmt;
    }
    return 0;
}