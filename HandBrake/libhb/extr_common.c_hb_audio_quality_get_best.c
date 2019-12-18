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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_audio_quality_get_limits (int /*<<< orphan*/ ,float*,float*,float*,int*) ; 

float hb_audio_quality_get_best(uint32_t codec, float quality)
{
    int direction;
    float low, high, granularity;
    hb_audio_quality_get_limits(codec, &low, &high, &granularity, &direction);
    if (quality > high)
        quality = high;
    if (quality < low)
        quality = low;
    return quality;
}