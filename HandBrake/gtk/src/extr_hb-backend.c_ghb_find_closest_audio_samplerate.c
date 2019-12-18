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
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ACODEC_INVALID ; 
 int /*<<< orphan*/  hb_audio_samplerate_find_closest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gint
ghb_find_closest_audio_samplerate(gint irate)
{
    return hb_audio_samplerate_find_closest(irate, HB_ACODEC_INVALID);
}