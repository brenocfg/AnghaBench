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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 

__attribute__((used)) static int64_t av_to_hb_pts( int64_t pts, double conv_factor, int64_t offset )
{
    if ( pts == AV_NOPTS_VALUE )
        return AV_NOPTS_VALUE;
    return (int64_t)( (double)pts * conv_factor ) - offset;
}