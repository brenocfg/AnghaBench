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
struct TYPE_3__ {int log2_chroma_w; int log2_chroma_h; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 

int av_pix_fmt_get_chroma_sub_sample(enum AVPixelFormat pix_fmt,
                                     int *h_shift, int *v_shift)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    if (!desc)
        return AVERROR(ENOSYS);
    *h_shift = desc->log2_chroma_w;
    *v_shift = desc->log2_chroma_h;

    return 0;
}