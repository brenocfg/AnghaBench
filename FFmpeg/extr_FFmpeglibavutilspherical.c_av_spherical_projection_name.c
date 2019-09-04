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
typedef  enum AVSphericalProjection { ____Placeholder_AVSphericalProjection } AVSphericalProjection ;

/* Variables and functions */
 unsigned int FF_ARRAY_ELEMS (char const**) ; 
 char const** spherical_projection_names ; 

const char *av_spherical_projection_name(enum AVSphericalProjection projection)
{
    if ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        return "unknown";

    return spherical_projection_names[projection];
}