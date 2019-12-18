#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int method; int /*<<< orphan*/  description; int /*<<< orphan*/  short_name; } ;
struct TYPE_4__ {TYPE_1__ item; } ;

/* Variables and functions */
 int hb_audio_dither_get_default () ; 
 TYPE_2__* hb_audio_dithers ; 
 int hb_audio_dithers_count ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int hb_audio_dither_get_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        goto fail;

    int i;
    for ( i = 0; i < hb_audio_dithers_count; i++)
    {
        if (!strcasecmp(hb_audio_dithers[i].item.short_name,  name) ||
            !strcasecmp(hb_audio_dithers[i].item.description, name))
        {
            return hb_audio_dithers[i].item.method;
        }
    }

fail:
    return hb_audio_dither_get_default();
}