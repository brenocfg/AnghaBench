#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rate; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ item; } ;
struct TYPE_7__ {int rate; } ;
struct TYPE_6__ {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ACODEC_INVALID ; 
 int atoi (char const*) ; 
 TYPE_4__* hb_audio_rates ; 
 int hb_audio_rates_count ; 
 TYPE_3__* hb_audio_rates_first_item ; 
 TYPE_2__* hb_audio_rates_last_item ; 
 int hb_audio_samplerate_find_closest (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int hb_audio_samplerate_get_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        goto fail;

    int i;
    for (i = 0; i < hb_audio_rates_count; i++)
    {
        if (!strcasecmp(hb_audio_rates[i].item.name, name))
        {
            return hb_audio_rates[i].item.rate;
        }
    }

    // maybe the samplerate was specified in Hz
    i = atoi(name);
    if (i >= hb_audio_rates_first_item->rate &&
        i <= hb_audio_rates_last_item ->rate)
    {
        return hb_audio_samplerate_find_closest(i, HB_ACODEC_INVALID);
    }

fail:
    return -1;
}