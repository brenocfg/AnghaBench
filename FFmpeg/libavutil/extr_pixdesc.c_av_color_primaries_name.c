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
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;

/* Variables and functions */
 unsigned int AVCOL_PRI_NB ; 
 char const** color_primaries_names ; 

const char *av_color_primaries_name(enum AVColorPrimaries primaries)
{
    return (unsigned) primaries < AVCOL_PRI_NB ?
        color_primaries_names[primaries] : NULL;
}