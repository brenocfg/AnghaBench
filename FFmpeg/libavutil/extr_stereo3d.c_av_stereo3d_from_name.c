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
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stereo3d_type_names ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

int av_stereo3d_from_name(const char *name)
{
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        size_t len = strlen(stereo3d_type_names[i]);
        if (!strncmp(stereo3d_type_names[i], name, len))
            return i;
    }

    return -1;
}