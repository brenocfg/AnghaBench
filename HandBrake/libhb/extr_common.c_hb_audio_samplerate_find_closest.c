#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int rate; } ;
typedef  TYPE_1__ hb_rate_t ;

/* Variables and functions */
 TYPE_1__* hb_audio_samplerate_get_next_for_codec (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

int hb_audio_samplerate_find_closest(int samplerate, uint32_t codec)
{
    const hb_rate_t * rate, * prev, * next;

    rate = prev = next = hb_audio_samplerate_get_next_for_codec(NULL, codec);

    if (rate == NULL)
    {
        // This codec doesn't support any samplerate
        return 0;
    }

    while (rate != NULL && next->rate < samplerate)
    {
        rate = hb_audio_samplerate_get_next_for_codec(rate, codec);
        if (rate != NULL)
        {
            prev = next;
            next = rate;
        }
    }

    int delta_prev = samplerate - prev->rate;
    int delta_next = next->rate - samplerate;
    if (delta_prev <= delta_next)
    {
        return prev->rate;
    }
    else
    {
        return next->rate;
    }
}