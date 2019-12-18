#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ type; scalar_t__* pixmap_server_handle; scalar_t__ pixmap; scalar_t__ name; } ;
struct TYPE_5__ {scalar_t__* pixmap_server_handle; scalar_t__ pixmap; int is_dup; TYPE_1__* process; } ;
struct TYPE_4__ {int /*<<< orphan*/  surfaces; } ;
typedef  TYPE_2__ PIXMAP_CHECK_DATA_T ;
typedef  int /*<<< orphan*/  KHRN_POINTER_MAP_T ;
typedef  TYPE_3__ EGL_SURFACE_T ;

/* Variables and functions */
 scalar_t__ PIXMAP ; 
 int /*<<< orphan*/  UNUSED_NDEBUG (scalar_t__) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

__attribute__((used)) static void callback_check_duplicate_pixmap(KHRN_POINTER_MAP_T *map, uint32_t key, void *value, void *data)
{
   PIXMAP_CHECK_DATA_T *pixmap_check_data = (PIXMAP_CHECK_DATA_T *)data;
   EGL_SURFACE_T *surface = (EGL_SURFACE_T *)value;

   UNUSED_NDEBUG(map);
   UNUSED_NDEBUG(key);

   vcos_assert(map == &pixmap_check_data->process->surfaces);
   vcos_assert(surface != NULL);
   vcos_assert((uintptr_t)key == (uintptr_t)surface->name);

   if ((surface->type == PIXMAP) && ((pixmap_check_data->pixmap_server_handle[0] || (pixmap_check_data->pixmap_server_handle[1] != (uint32_t)-1)) ?
      /* compare server handles for server-side pixmaps */
      ((surface->pixmap_server_handle[0] == pixmap_check_data->pixmap_server_handle[0]) &&
      (surface->pixmap_server_handle[1] == pixmap_check_data->pixmap_server_handle[1])) :
      /* compare EGLNativePixmapType for client-side pixmaps */
      (!surface->pixmap_server_handle[0] && (surface->pixmap_server_handle[1] == (uint32_t)-1) &&
      (surface->pixmap == pixmap_check_data->pixmap)))) {
      pixmap_check_data->is_dup = 1;
   }
}