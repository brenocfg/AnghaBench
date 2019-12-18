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
struct TYPE_6__ {int amixdown; char const* short_name; } ;
typedef  TYPE_1__ hb_mixdown_t ;
struct TYPE_8__ {int amixdown; } ;
struct TYPE_7__ {int amixdown; } ;

/* Variables and functions */
 TYPE_5__* hb_audio_mixdowns_first_item ; 
 TYPE_4__* hb_audio_mixdowns_last_item ; 
 TYPE_1__* hb_mixdown_get_next (TYPE_1__ const*) ; 

const char* hb_mixdown_get_short_name(int mixdown)
{
    if (mixdown < hb_audio_mixdowns_first_item->amixdown ||
        mixdown > hb_audio_mixdowns_last_item ->amixdown)
        goto fail;

    const hb_mixdown_t *audio_mixdown = NULL;
    while ((audio_mixdown = hb_mixdown_get_next(audio_mixdown)) != NULL)
    {
        if (audio_mixdown->amixdown == mixdown)
        {
            return audio_mixdown->short_name;
        }
    }

fail:
    return NULL;
}