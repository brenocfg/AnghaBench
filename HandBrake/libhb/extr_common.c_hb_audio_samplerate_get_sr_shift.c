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

int hb_audio_samplerate_get_sr_shift(int samplerate)
{
    /* sr_shift: 0 -> 48000, 44100, 32000 Hz
     *           1 -> 24000, 22050, 16000 Hz
     *           2 -> 12000, 11025,  8000 Hz
     *
     * also, since samplerates are sanitized downwards:
     *
     * (samplerate < 32000) implies (samplerate <= 24000)
     */
    return ((samplerate < 16000) ? 2 : (samplerate < 32000) ? 1 : 0);
}