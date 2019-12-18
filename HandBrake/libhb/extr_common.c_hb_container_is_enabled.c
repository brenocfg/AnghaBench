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
#define  HB_MUX_AV_MKV 130 
#define  HB_MUX_AV_MP4 129 
#define  HB_MUX_AV_WEBM 128 

__attribute__((used)) static int hb_container_is_enabled(int format)
{
    switch (format)
    {
        case HB_MUX_AV_MP4:
        case HB_MUX_AV_MKV:
        case HB_MUX_AV_WEBM:
            return 1;

        default:
            return 0;
    }
}