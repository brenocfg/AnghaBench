#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  rate; } ;
typedef  TYPE_1__ hb_rate_t ;

/* Variables and functions */
 TYPE_1__* hb_audio_samplerate_get_next (TYPE_1__ const*) ; 
 scalar_t__ hb_audio_samplerate_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const hb_rate_t* hb_audio_samplerate_get_next_for_codec(const hb_rate_t *last,
                                                        uint32_t codec)
{
    while ((last = hb_audio_samplerate_get_next(last)) != NULL)
        if (hb_audio_samplerate_is_supported(last->rate, codec))
            return last;

    // None found or end of list
    return NULL;
}