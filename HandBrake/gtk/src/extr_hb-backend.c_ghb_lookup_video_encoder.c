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
struct TYPE_5__ {int codec; } ;
typedef  TYPE_1__ hb_encoder_t ;

/* Variables and functions */
 int hb_video_encoder_get_from_name (char const*) ; 
 TYPE_1__* hb_video_encoder_get_next (TYPE_1__ const*) ; 

const hb_encoder_t*
ghb_lookup_video_encoder(const char *name)
{
    // First find an enabled encoder
    int codec = hb_video_encoder_get_from_name(name);

    // Now find the matching encoder info
    const hb_encoder_t *enc, *first;
    for (first = enc = hb_video_encoder_get_next(NULL); enc != NULL;
         enc = hb_video_encoder_get_next(enc))
    {
        if (codec == enc->codec)
        {
            return enc;
        }
    }
    // Return a default encoder if nothing matches
    return first;
}