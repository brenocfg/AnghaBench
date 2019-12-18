#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int*) ; 
 int av_get_channel_layout_nb_channels (int) ; 
 int* thd_channel_order ; 

__attribute__((used)) static uint64_t thd_channel_layout_extract_channel(uint64_t channel_layout,
                                                   int index)
{
    int i;

    if (av_get_channel_layout_nb_channels(channel_layout) <= index)
        return 0;

    for (i = 0; i < FF_ARRAY_ELEMS(thd_channel_order); i++)
        if (channel_layout & thd_channel_order[i] && !index--)
            return thd_channel_order[i];
    return 0;
}