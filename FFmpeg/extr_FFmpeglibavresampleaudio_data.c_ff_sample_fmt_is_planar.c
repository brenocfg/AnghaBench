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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int av_sample_fmt_is_planar (int) ; 

int ff_sample_fmt_is_planar(enum AVSampleFormat sample_fmt, int channels)
{
    if (channels == 1)
        return 1;
    else
        return av_sample_fmt_is_planar(sample_fmt);
}