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
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;

/* Variables and functions */
 unsigned int AVCOL_SPC_NB ; 
 char const** color_space_names ; 

const char *av_color_space_name(enum AVColorSpace space)
{
    return (unsigned) space < AVCOL_SPC_NB ?
        color_space_names[space] : NULL;
}