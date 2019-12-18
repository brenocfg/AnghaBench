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
#define  HB_AMIXDOWN_5POINT1 131 
#define  HB_AMIXDOWN_5_2_LFE 130 
#define  HB_AMIXDOWN_6POINT1 129 
#define  HB_AMIXDOWN_7POINT1 128 

int hb_mixdown_get_low_freq_channel_count(int amixdown)
{
    switch (amixdown)
    {
        case HB_AMIXDOWN_5POINT1:
        case HB_AMIXDOWN_6POINT1:
        case HB_AMIXDOWN_7POINT1:
        case HB_AMIXDOWN_5_2_LFE:
            return 1;

        default:
            return 0;
    }
}