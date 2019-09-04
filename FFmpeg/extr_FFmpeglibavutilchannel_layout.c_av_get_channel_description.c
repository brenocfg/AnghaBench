#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_3__ {char const* description; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int av_get_channel_layout_nb_channels (unsigned long long) ; 
 TYPE_1__* channel_names ; 

const char *av_get_channel_description(uint64_t channel)
{
    int i;
    if (av_get_channel_layout_nb_channels(channel) != 1)
        return NULL;
    for (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++)
        if ((1ULL<<i) & channel)
            return channel_names[i].description;
    return NULL;
}