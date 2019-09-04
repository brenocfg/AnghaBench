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
typedef  enum AVColorRange { ____Placeholder_AVColorRange } AVColorRange ;

/* Variables and functions */
 unsigned int AVCOL_RANGE_NB ; 
 char const** color_range_names ; 

const char *av_color_range_name(enum AVColorRange range)
{
    return (unsigned) range < AVCOL_RANGE_NB ?
        color_range_names[range] : NULL;
}