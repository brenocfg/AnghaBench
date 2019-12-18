#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rate; } ;
typedef  TYPE_1__ hb_rate_t ;
struct TYPE_6__ {int rate; } ;

/* Variables and functions */
 TYPE_1__* hb_audio_bitrate_get_next (TYPE_1__ const*) ; 
 TYPE_2__* hb_audio_bitrates_first_item ; 

__attribute__((used)) static int hb_audio_bitrate_find_closest(int bitrate)
{
    // Check if bitrate mode was disabled
    if (bitrate <= 0)
        return bitrate;

    int closest_bitrate            = hb_audio_bitrates_first_item->rate;
    const hb_rate_t *audio_bitrate = NULL;
    while ((audio_bitrate = hb_audio_bitrate_get_next(audio_bitrate)) != NULL)
    {
        if (bitrate == audio_bitrate->rate)
        {
            // valid bitrate
            closest_bitrate = audio_bitrate->rate;
            break;
        }
        if (bitrate > audio_bitrate->rate)
        {
            // bitrates are sanitized downwards
            closest_bitrate = audio_bitrate->rate;
        }
    }
    return closest_bitrate;
}