#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int codec; } ;
typedef  TYPE_1__ hb_encoder_t ;
struct TYPE_5__ {TYPE_1__ item; } ;

/* Variables and functions */
 TYPE_2__* hb_video_encoders ; 
 int hb_video_encoders_count ; 

hb_encoder_t * hb_video_encoder_get_from_codec(int codec)
{
    int i;
    for (i = 0; i < hb_video_encoders_count; i++)
    {
        if (hb_video_encoders[i].item.codec == codec)
        {
            return &hb_video_encoders[i].item;
        }
    }

    return NULL;
}