#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  VGImageFormat ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  pixmap; } ;
struct TYPE_6__ {scalar_t__ type; int const height; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_TYPE_T ;
typedef  TYPE_2__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ GX_PBUFFER ; 
 scalar_t__ GX_WINDOW ; 
 scalar_t__ VCOS_EINVAL ; 
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ convert_image_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ vgGetError () ; 
 int /*<<< orphan*/  vgImageSubData (int /*<<< orphan*/ ,void const*,int const,int /*<<< orphan*/ ,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  vgWritePixels (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int const,int const,int const,int const) ; 

int32_t graphics_userblt(GRAPHICS_RESOURCE_TYPE_T src_type,
                         const void *src_data,
                         const uint32_t src_x,
                         const uint32_t src_y,
                         const uint32_t width,
                         const uint32_t height,
                         const uint32_t pitch,
                         GRAPHICS_RESOURCE_HANDLE dest,
                         const uint32_t x_pos,
                         const uint32_t y_pos )
{
   VCOS_STATUS_T status;
   VGImageFormat vg_src_type;
   int bytes_per_pixel;
   GX_CLIENT_STATE_T save;

   status = convert_image_type(src_type, &vg_src_type, &bytes_per_pixel);
   if (status != VCOS_SUCCESS)
      return status;

   gx_priv_save(&save, dest);

   if (dest->type == GX_PBUFFER)
   {
      vgImageSubData(dest->u.pixmap,
                     src_data,
                     pitch,
                     vg_src_type,
                     x_pos, y_pos, width, height);
   }
   else if (dest->type == GX_WINDOW)
   {
      // need to invert this as VG thinks zero is at the bottom
      // while graphics_x thinks it is at the top.
      vgWritePixels((uint8_t*)src_data + pitch*(height-1),
                    -pitch,
                    vg_src_type,
                    x_pos, dest->height-y_pos-height, width, height);
   }
   else
   {
      vcos_assert(0);
   }

   if (vgGetError() == 0)
      status = VCOS_SUCCESS;
   else
   {
      vcos_assert(0);
      status = VCOS_EINVAL;
   }

   gx_priv_restore(&save);
   return status;
}