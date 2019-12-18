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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ av_get_channel_layout (char const*) ; 
 int av_get_channel_layout_nb_channels (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int strtol (char const*,char**,int) ; 

int av_get_extended_channel_layout(const char *name, uint64_t* channel_layout, int* nb_channels)
{
    int nb = 0;
    char *end;
    uint64_t layout = av_get_channel_layout(name);

    if (layout) {
        *channel_layout = layout;
        *nb_channels = av_get_channel_layout_nb_channels(layout);
        return 0;
    }

    nb = strtol(name, &end, 10);
    if (!errno && *end  == 'C' && *(end + 1) == '\0' && nb > 0 && nb < 64) {
        *channel_layout = 0;
        *nb_channels = nb;
        return 0;
    }

    return AVERROR(EINVAL);
}