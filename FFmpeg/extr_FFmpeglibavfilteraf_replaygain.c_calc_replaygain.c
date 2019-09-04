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
typedef  int uint32_t ;

/* Variables and functions */
 int HISTOGRAM_SLOTS ; 
 float av_clipf (float,double,double) ; 

__attribute__((used)) static float calc_replaygain(uint32_t *histogram)
{
    uint32_t loud_count = 0, total_windows = 0;
    float gain;
    int i;

    for (i = 0; i < HISTOGRAM_SLOTS; i++)
        total_windows += histogram [i];

    while (i--)
        if ((loud_count += histogram [i]) * 20 >= total_windows)
            break;

    gain = (float)(64.54 - i / 100.0);

    return av_clipf(gain, -24.0, 64.0);
}