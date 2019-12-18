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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int nb_components; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int FF_ARRAY_ELEMS (int**) ; 
 int av_pix_fmt_count_planes (int) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int** deinterleaved_formats ; 

__attribute__((used)) static enum AVPixelFormat get_deinterleaved_format(enum AVPixelFormat fmt)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(fmt);
    int i, planes;

    planes = av_pix_fmt_count_planes(fmt);
    if (planes == desc->nb_components)
        return fmt;
    for (i = 0; i < FF_ARRAY_ELEMS(deinterleaved_formats); i++)
        if (deinterleaved_formats[i][0] == fmt)
            return deinterleaved_formats[i][1];
    return AV_PIX_FMT_NONE;
}