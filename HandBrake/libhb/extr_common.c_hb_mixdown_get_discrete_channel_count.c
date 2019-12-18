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
#define  HB_AMIXDOWN_5POINT1 135 
#define  HB_AMIXDOWN_5_2_LFE 134 
#define  HB_AMIXDOWN_6POINT1 133 
#define  HB_AMIXDOWN_7POINT1 132 
#define  HB_AMIXDOWN_LEFT 131 
#define  HB_AMIXDOWN_MONO 130 
#define  HB_AMIXDOWN_NONE 129 
#define  HB_AMIXDOWN_RIGHT 128 

int hb_mixdown_get_discrete_channel_count(int amixdown)
{
    switch (amixdown)
    {
        case HB_AMIXDOWN_5_2_LFE:
        case HB_AMIXDOWN_7POINT1:
            return 8;

        case HB_AMIXDOWN_6POINT1:
            return 7;

        case HB_AMIXDOWN_5POINT1:
            return 6;

        case HB_AMIXDOWN_MONO:
        case HB_AMIXDOWN_LEFT:
        case HB_AMIXDOWN_RIGHT:
            return 1;

        case HB_AMIXDOWN_NONE:
            return 0;

        default:
            return 2;
    }
}