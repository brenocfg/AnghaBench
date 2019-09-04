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
struct TYPE_5__ {int mode; unsigned int channels; TYPE_1__* d; } ;
struct TYPE_4__ {double* sample_peak; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_EBUR128_MODE_SAMPLE_PEAK ; 

int ff_ebur128_sample_peak(FFEBUR128State * st,
                           unsigned int channel_number, double *out)
{
    if ((st->mode & FF_EBUR128_MODE_SAMPLE_PEAK) !=
        FF_EBUR128_MODE_SAMPLE_PEAK) {
        return AVERROR(EINVAL);
    } else if (channel_number >= st->channels) {
        return AVERROR(EINVAL);
    }
    *out = st->d->sample_peak[channel_number];
    return 0;
}