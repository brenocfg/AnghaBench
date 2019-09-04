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
typedef  scalar_t__ uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {scalar_t__ cv_fmt; int pix_fmt; } ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* cv_pix_fmts ; 

enum AVPixelFormat av_map_videotoolbox_format_to_pixfmt(uint32_t cv_fmt)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(cv_pix_fmts); i++) {
        if (cv_pix_fmts[i].cv_fmt == cv_fmt)
            return cv_pix_fmts[i].pix_fmt;
    }
    return AV_PIX_FMT_NONE;
}