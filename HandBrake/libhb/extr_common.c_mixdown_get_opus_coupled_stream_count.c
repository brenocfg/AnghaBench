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
#define  HB_AMIXDOWN_5POINT1 136 
#define  HB_AMIXDOWN_5_2_LFE 135 
#define  HB_AMIXDOWN_6POINT1 134 
#define  HB_AMIXDOWN_7POINT1 133 
#define  HB_AMIXDOWN_LEFT 132 
#define  HB_AMIXDOWN_MONO 131 
#define  HB_AMIXDOWN_NONE 130 
#define  HB_AMIXDOWN_RIGHT 129 
#define  HB_INVALID_AMIXDOWN 128 

__attribute__((used)) static int mixdown_get_opus_coupled_stream_count(int mixdown)
{
    switch (mixdown)
    {
        case HB_AMIXDOWN_7POINT1:
        case HB_AMIXDOWN_6POINT1:
            return 3;

        case HB_AMIXDOWN_5POINT1:
            return 2;

        case HB_AMIXDOWN_MONO:
        case HB_AMIXDOWN_LEFT:
        case HB_AMIXDOWN_RIGHT:
            return 0;

        case HB_AMIXDOWN_NONE:
        case HB_INVALID_AMIXDOWN:
        case HB_AMIXDOWN_5_2_LFE:
            // The 5F/2R/LFE configuration is currently not supported by Opus,
            // so don't set coupled streams.
            return 0;

        default:
            return 1;
    }
}