#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  plane_id; } ;
typedef  TYPE_1__ drmModePlane ;
typedef  TYPE_2__* drmModeObjectPropertiesPtr ;
struct TYPE_10__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int count_props; int /*<<< orphan*/ * prop_values; int /*<<< orphan*/ * props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_PLANE ; 
 TYPE_6__ drm ; 
 TYPE_5__* drmModeGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* drmModeObjectGetProperties (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint64_t drm_plane_type(drmModePlane *plane)
{
   int i,j;

   /* The property values and their names are stored in different arrays,
    * so we access them simultaneously here.
    * We are interested in OVERLAY planes only, that's
    * type 0 or DRM_PLANE_TYPE_OVERLAY
    * (see /usr/xf86drmMode.h for definition). */
   drmModeObjectPropertiesPtr props =
      drmModeObjectGetProperties(drm.fd, plane->plane_id,
            DRM_MODE_OBJECT_PLANE);

   for (j = 0; j < props->count_props; j++)
   {
      /* found the type property */
      if (string_is_equal(
               drmModeGetProperty(drm.fd, props->props[j])->name, "type"))
         return (props->prop_values[j]);
   }

   return (0);
}