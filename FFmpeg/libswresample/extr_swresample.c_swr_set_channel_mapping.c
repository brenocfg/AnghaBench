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
struct SwrContext {int const* channel_map; scalar_t__ in_convert; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 

int swr_set_channel_mapping(struct SwrContext *s, const int *channel_map){
    if(!s || s->in_convert) // s needs to be allocated but not initialized
        return AVERROR(EINVAL);
    s->channel_map = channel_map;
    return 0;
}