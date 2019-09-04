#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_2__ {int bits; } ;

/* Variables and functions */
 int AV_SAMPLE_FMT_NB ; 
 TYPE_1__* sample_fmt_info ; 

int av_get_bytes_per_sample(enum AVSampleFormat sample_fmt)
{
     return sample_fmt < 0 || sample_fmt >= AV_SAMPLE_FMT_NB ?
        0 : sample_fmt_info[sample_fmt].bits >> 3;
}