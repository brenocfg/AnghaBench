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
struct TYPE_4__ {int codec; char const* name; } ;
typedef  TYPE_1__ hb_encoder_t ;

/* Variables and functions */
 int HB_VCODEC_MASK ; 
 TYPE_1__* hb_video_encoder_get_next (TYPE_1__ const*) ; 

const char* hb_video_encoder_get_name(int encoder)
{
    if (!(encoder & HB_VCODEC_MASK))
        goto fail;

    const hb_encoder_t *video_encoder = NULL;
    while ((video_encoder = hb_video_encoder_get_next(video_encoder)) != NULL)
    {
        if (video_encoder->codec == encoder)
        {
            return video_encoder->name;
        }
    }

fail:
    return NULL;
}