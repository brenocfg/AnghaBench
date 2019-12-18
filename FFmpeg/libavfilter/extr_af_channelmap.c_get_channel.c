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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_get_channel_layout (char*) ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 char* split (char*,char) ; 

__attribute__((used)) static int get_channel(char **map, uint64_t *ch, char delim)
{
    char *next = split(*map, delim);
    if (!next && delim == '-')
        return AVERROR(EINVAL);
    *ch = av_get_channel_layout(*map);
    if (av_get_channel_layout_nb_channels(*ch) != 1)
        return AVERROR(EINVAL);
    *map = next;
    return 0;
}