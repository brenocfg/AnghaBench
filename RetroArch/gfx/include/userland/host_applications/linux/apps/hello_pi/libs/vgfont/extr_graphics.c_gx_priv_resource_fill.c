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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VGfloat ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GX_LOG (char*,int) ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_CLEAR_COLOR ; 
 int /*<<< orphan*/  VG_FALSE ; 
 int /*<<< orphan*/  VG_SCISSORING ; 
 int /*<<< orphan*/  gx_priv_colour_to_paint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgClear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vgGetError () ; 
 int /*<<< orphan*/  vgSetfv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgSeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VCOS_STATUS_T gx_priv_resource_fill(GRAPHICS_RESOURCE_HANDLE res,
                               uint32_t x,
                               uint32_t y,
                               uint32_t width,
                               uint32_t height,
                               uint32_t fill_colour )
{
   VGfloat vg_clear_colour[4];

   gx_priv_colour_to_paint(fill_colour, vg_clear_colour);
   vgSeti(VG_SCISSORING, VG_FALSE);

   vgSetfv(VG_CLEAR_COLOR, 4, vg_clear_colour);
   vgClear(x, y, width, height);

   int err = vgGetError();
   if (err)
   {
      GX_LOG("vg error %x filling area", err);
      vcos_assert(0);
   }

   return VCOS_SUCCESS;
}