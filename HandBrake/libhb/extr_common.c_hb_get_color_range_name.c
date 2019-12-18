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
#define  AVCOL_RANGE_JPEG 129 
#define  AVCOL_RANGE_MPEG 128 

const char * hb_get_color_range_name(int range)
{
    switch (range)
    {
        case AVCOL_RANGE_MPEG:
            return "mpeg";
        case AVCOL_RANGE_JPEG:
            return "jpeg";
        default:
            return "mpeg";
    }
}