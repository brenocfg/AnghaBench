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
typedef  int /*<<< orphan*/  AVFilterFormats ;

/* Variables and functions */
 scalar_t__ av_get_bytes_per_sample (int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 
 scalar_t__ ff_add_format (int /*<<< orphan*/ **,int) ; 

AVFilterFormats *ff_planar_sample_fmts(void)
{
    AVFilterFormats *ret = NULL;
    int fmt;

    for (fmt = 0; av_get_bytes_per_sample(fmt)>0; fmt++)
        if (av_sample_fmt_is_planar(fmt))
            if (ff_add_format(&ret, fmt) < 0)
                return NULL;

    return ret;
}