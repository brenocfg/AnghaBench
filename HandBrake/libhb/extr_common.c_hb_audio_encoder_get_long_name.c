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
struct TYPE_4__ {int codec; char const* long_name; } ;
typedef  TYPE_1__ hb_encoder_t ;

/* Variables and functions */
 int HB_ACODEC_ANY ; 
 TYPE_1__* hb_audio_encoder_get_next (TYPE_1__ const*) ; 

const char* hb_audio_encoder_get_long_name(int encoder)
{
    if (!(encoder & HB_ACODEC_ANY))
        goto fail;

    const hb_encoder_t *audio_encoder = NULL;
    while ((audio_encoder = hb_audio_encoder_get_next(audio_encoder)) != NULL)
    {
        if (audio_encoder->codec == encoder)
        {
            return audio_encoder->long_name;
        }
    }

fail:
    return NULL;
}