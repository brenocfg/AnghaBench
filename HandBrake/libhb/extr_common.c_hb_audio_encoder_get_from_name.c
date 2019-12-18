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
struct TYPE_3__ {int codec; int /*<<< orphan*/  short_name; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ item; } ;

/* Variables and functions */
 int HB_ACODEC_INVALID ; 
 TYPE_2__* hb_audio_encoders ; 
 int hb_audio_encoders_count ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int hb_audio_encoder_get_from_name(const char *name)
{
    if (name == NULL || *name == '\0')
        goto fail;

    int i;
    for (i = 0; i < hb_audio_encoders_count; i++)
    {
        if (!strcasecmp(hb_audio_encoders[i].item.name,       name) ||
            !strcasecmp(hb_audio_encoders[i].item.short_name, name))
        {
            return hb_audio_encoders[i].item.codec;
        }
    }

fail:
    return HB_ACODEC_INVALID;
}