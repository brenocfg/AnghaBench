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
typedef  int int64_t ;

/* Variables and functions */
 int AV_CH_LAYOUT_NATIVE ; 

__attribute__((used)) static int is_mono(uint64_t layout)
{
    int ii, channel_count;
    int64_t mask;

    if (layout == AV_CH_LAYOUT_NATIVE)
    {
        return 0;
    }
    for (ii = 0, channel_count = 0, mask = 1;
         ii < 64 && channel_count < 2; ii++, mask <<= 1)
    {
        if (layout & mask)
        {
            channel_count++;
        }
    }
    return channel_count == 1;
}