#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f; } ;
struct TYPE_5__ {TYPE_1__ tf; } ;
typedef  TYPE_2__ VP9Frame ;
typedef  int /*<<< orphan*/  VASurfaceID ;

/* Variables and functions */
 int /*<<< orphan*/  VA_INVALID_SURFACE ; 
 int /*<<< orphan*/  ff_vaapi_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VASurfaceID vaapi_vp9_surface_id(const VP9Frame *vf)
{
    if (vf)
        return ff_vaapi_get_surface_id(vf->tf.f);
    else
        return VA_INVALID_SURFACE;
}