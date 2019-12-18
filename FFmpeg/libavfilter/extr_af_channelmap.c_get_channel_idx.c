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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 char* split (char*,char) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int get_channel_idx(char **map, int *ch, char delim, int max_ch)
{
    char *next;
    int len;
    int n = 0;
    if (!*map)
        return AVERROR(EINVAL);
    next = split(*map, delim);
    if (!next && delim == '-')
        return AVERROR(EINVAL);
    len = strlen(*map);
    sscanf(*map, "%d%n", ch, &n);
    if (n != len)
        return AVERROR(EINVAL);
    if (*ch < 0 || *ch > max_ch)
        return AVERROR(EINVAL);
    *map = next;
    return 0;
}