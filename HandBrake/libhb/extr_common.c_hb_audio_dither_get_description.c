#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int method; char const* description; } ;
typedef  TYPE_1__ hb_dither_t ;
struct TYPE_8__ {int method; } ;
struct TYPE_7__ {int method; } ;

/* Variables and functions */
 TYPE_1__* hb_audio_dither_get_next (TYPE_1__ const*) ; 
 TYPE_3__* hb_audio_dithers_first_item ; 
 TYPE_2__* hb_audio_dithers_last_item ; 

const char* hb_audio_dither_get_description(int method)
{
    if (method < hb_audio_dithers_first_item->method ||
        method > hb_audio_dithers_last_item ->method)
        goto fail;

    const hb_dither_t *audio_dither = NULL;
    while ((audio_dither = hb_audio_dither_get_next(audio_dither)) != NULL)
    {
        if (audio_dither->method == method)
        {
            return audio_dither->description;
        }
    }

fail:
    return NULL;
}