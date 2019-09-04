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
 unsigned int FF_ARRAY_ELEMS (char const**) ; 
 char const** stereo3d_type_names ; 

const char *av_stereo3d_type_name(unsigned int type)
{
    if (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        return "unknown";

    return stereo3d_type_names[type];
}