#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int amixdown; } ;
typedef  TYPE_1__ hb_mixdown_t ;
struct TYPE_5__ {TYPE_1__ item; } ;

/* Variables and functions */
 TYPE_3__* hb_audio_mixdowns ; 
 int hb_audio_mixdowns_count ; 

hb_mixdown_t* hb_mixdown_get_from_mixdown(int mixdown)
{
    int i;
    for (i = 0; i < hb_audio_mixdowns_count; i++)
    {
        if (hb_audio_mixdowns[i].item.amixdown == mixdown)
        {
            return &hb_audio_mixdowns[i].item;
        }
    }

    return NULL;
}