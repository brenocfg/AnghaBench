#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bit_depth; } ;
typedef  TYPE_1__ x264_api_t ;

/* Variables and functions */
 int HB_X264_API_COUNT ; 
 TYPE_1__ const* x264_apis ; 

const x264_api_t * hb_x264_api_get(int bit_depth)
{
    int ii;

    for (ii = 0; ii < HB_X264_API_COUNT; ii++)
    {
        if (-1        != x264_apis[ii].bit_depth &&
            bit_depth == x264_apis[ii].bit_depth)
        {
            return &x264_apis[ii];
        }
    }
    return NULL;
}