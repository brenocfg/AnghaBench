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
 int hb_audio_bitrate_find_closest (int) ; 
 int /*<<< orphan*/  hb_audio_bitrate_get_limits (int /*<<< orphan*/ ,int,int,int*,int*) ; 

int hb_audio_bitrate_get_best(uint32_t codec, int bitrate, int samplerate,
                              int mixdown)
{
    int low, high;
    hb_audio_bitrate_get_limits(codec, samplerate, mixdown, &low, &high);
    if (bitrate > high)
        bitrate = high;
    if (bitrate < low)
        bitrate = low;
    return hb_audio_bitrate_find_closest(bitrate);
}