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
 int SWR_DITHER_TRIANGULAR ; 

int hb_audio_dither_get_default_method()
{
    /*
     * input could be s16 (possibly already dithered) converted to flt, so
     * let's use a "low-risk" dither algorithm (standard triangular).
     */
    return SWR_DITHER_TRIANGULAR;
}