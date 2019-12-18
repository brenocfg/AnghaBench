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
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static int get_duration(const char *buf)
{
    int frame_start, frame_end;

    if (sscanf(buf, "{%d}{%d}", &frame_start, &frame_end) == 2)
        return frame_end - frame_start;
    return -1;
}