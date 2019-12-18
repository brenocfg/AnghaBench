#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rate; char const* name; } ;
typedef  TYPE_1__ hb_rate_t ;
struct TYPE_8__ {int rate; } ;
struct TYPE_7__ {int rate; } ;

/* Variables and functions */
 TYPE_5__* hb_audio_rates_first_item ; 
 TYPE_4__* hb_audio_rates_last_item ; 
 TYPE_1__* hb_audio_samplerate_get_next (TYPE_1__ const*) ; 

const char* hb_audio_samplerate_get_name(int samplerate)
{
    if (samplerate < hb_audio_rates_first_item->rate ||
        samplerate > hb_audio_rates_last_item ->rate)
        goto fail;

    const hb_rate_t *audio_samplerate = NULL;
    while ((audio_samplerate = hb_audio_samplerate_get_next(audio_samplerate)) != NULL)
    {
        if (audio_samplerate->rate == samplerate)
        {
            return audio_samplerate->name;
        }
    }

fail:
    return NULL;
}