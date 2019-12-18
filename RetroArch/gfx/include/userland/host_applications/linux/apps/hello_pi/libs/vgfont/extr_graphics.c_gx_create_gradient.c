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
typedef  double VGfloat ;
typedef  scalar_t__ VGPaint ;
typedef  int /*<<< orphan*/  GX_PAINT_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ VG_INVALID_HANDLE ; 
 int /*<<< orphan*/  VG_PAINT_COLOR_RAMP_STOPS ; 
 int /*<<< orphan*/  VG_PAINT_TYPE ; 
 int /*<<< orphan*/  VG_PAINT_TYPE_LINEAR_GRADIENT ; 
 int /*<<< orphan*/  gx_priv_colour_to_paint (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vgCreatePaint () ; 
 int /*<<< orphan*/  vgGetError () ; 
 int /*<<< orphan*/  vgSetParameterfv (scalar_t__,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  vgSetParameteri (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GX_PAINT_T *gx_create_gradient(GRAPHICS_RESOURCE_HANDLE res,
                               uint32_t start_colour,
                               uint32_t end_colour)
{
   // holds  the two colour stops (offset,r,g,b,a).
   VGfloat fill_stops[10];
   GX_CLIENT_STATE_T save;
   VGPaint paint = VG_INVALID_HANDLE;

   gx_priv_save(&save, res);

   paint = vgCreatePaint();
   if (!paint)
   {
      gx_priv_restore(&save);
      vcos_log("Could not create paint: vg %d\n", vgGetError());
      vcos_assert(0);
      goto finish;
   }

   fill_stops[0] = 0.0;
   gx_priv_colour_to_paint(start_colour, fill_stops+1);

   fill_stops[5] = 1.0;
   gx_priv_colour_to_paint(end_colour, fill_stops+6);

   vgSetParameteri(paint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
   vgSetParameterfv(paint, VG_PAINT_COLOR_RAMP_STOPS, 5*2, fill_stops);

finish:
   gx_priv_restore(&save);
   return (GX_PAINT_T*)paint;
}