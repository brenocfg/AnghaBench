#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {scalar_t__ prop_id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ drmModePropertyRes ;
struct TYPE_13__ {int count_planes; int /*<<< orphan*/ * planes; } ;
typedef  TYPE_2__ drmModePlaneRes ;
struct TYPE_14__ {scalar_t__ plane_id; } ;
typedef  TYPE_3__ drmModePlane ;
struct TYPE_15__ {int count_props; int /*<<< orphan*/ * props; } ;
typedef  TYPE_4__ drmModeObjectProperties ;
struct TYPE_11__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_PLANE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,scalar_t__,char const*) ; 
 TYPE_10__ drm ; 
 TYPE_3__* drmModeGetPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* drmModeGetPlaneResources (int /*<<< orphan*/ ) ; 
 TYPE_1__* drmModeGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* drmModeObjectGetProperties (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__** malloc (int) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static uint32_t get_plane_prop_id(uint32_t obj_id, const char *name)
{
   int i,j;
   drmModePlaneRes *plane_resources;
   drmModePlane *plane;
   drmModeObjectProperties *props;
   drmModePropertyRes **props_info;

   char format_str[5];

   plane_resources = drmModeGetPlaneResources(drm.fd);
   for (i = 0; i < plane_resources->count_planes; i++)
   {
      plane = drmModeGetPlane(drm.fd, plane_resources->planes[i]);
      if (plane->plane_id != obj_id)
         continue;

      /* TODO: Improvement. We get all the properties of the
       * plane and info about the properties.
       * We should have done this already...
       * This implementation must be improved. */
      props      = drmModeObjectGetProperties(drm.fd,
            plane->plane_id, DRM_MODE_OBJECT_PLANE);
      props_info = malloc(props->count_props * sizeof *props_info);

      for (j = 0; j < props->count_props; ++j)
         props_info[j] =	drmModeGetProperty(drm.fd, props->props[j]);

      /* We look for the prop_id we need */
      for (j = 0; j < props->count_props; j++)
      {
         if (string_is_equal(props_info[j]->name, name))
            return props_info[j]->prop_id;
      }
      RARCH_ERR ("DRM: plane %d fb property ID with name %s not found\n",
            plane->plane_id, name);
   }
   return (0);
}