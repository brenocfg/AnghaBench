#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {int nb_components; TYPE_1__* comp; } ;
struct TYPE_4__ {size_t plane; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (int*) ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 

int av_pix_fmt_count_planes(enum AVPixelFormat pix_fmt)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    int i, planes[4] = { 0 }, ret = 0;

    if (!desc)
        return AVERROR(EINVAL);

    for (i = 0; i < desc->nb_components; i++)
        planes[desc->comp[i].plane] = 1;
    for (i = 0; i < FF_ARRAY_ELEMS(planes); i++)
        ret += planes[i];
    return ret;
}