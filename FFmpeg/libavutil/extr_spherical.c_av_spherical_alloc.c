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
typedef  int /*<<< orphan*/  AVSphericalMapping ;

/* Variables and functions */
 int /*<<< orphan*/ * av_mallocz (int) ; 

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(sizeof(AVSphericalMapping));
    if (!spherical)
        return NULL;

    if (size)
        *size = sizeof(*spherical);

    return spherical;
}