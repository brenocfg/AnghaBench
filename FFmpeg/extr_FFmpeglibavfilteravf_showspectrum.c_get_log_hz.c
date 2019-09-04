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

/* Variables and functions */
 int log_scale (float const,int,float const) ; 

__attribute__((used)) static float get_log_hz(const int bin, const int num_bins, const float sample_rate)
{
    const float max_freq = sample_rate / 2;
    const float hz_per_bin = max_freq / num_bins;
    const float freq = hz_per_bin * bin;
    const float scaled_freq = log_scale(freq + 1, 21, max_freq) - 1;

    return num_bins * scaled_freq / max_freq;
}