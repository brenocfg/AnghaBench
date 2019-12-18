#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ hb_rate_t ;

/* Variables and functions */
 TYPE_1__* hb_audio_bitrate_get_next (TYPE_1__ const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

const hb_rate_t*
ghb_lookup_audio_bitrate(const char *name)
{
    // Now find the matching rate info
    const hb_rate_t *hb_rate;
    for (hb_rate = hb_audio_bitrate_get_next(NULL); hb_rate != NULL;
         hb_rate = hb_audio_bitrate_get_next(hb_rate))
    {
        if (!strncmp(name, hb_rate->name, 8))
        {
            return hb_rate;
        }
    }
    // Return a default rate if nothing matches
    return NULL;
}