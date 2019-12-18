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
typedef  int int32_t ;
typedef  int VGfloat ;
typedef  int /*<<< orphan*/  VGPath ;
typedef  int /*<<< orphan*/  VGPaint ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  int /*<<< orphan*/  GX_PAINT_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_FILL_PATH ; 
 int /*<<< orphan*/  VG_PAINT_LINEAR_GRADIENT ; 
 int /*<<< orphan*/  VG_PATH_CAPABILITY_ALL ; 
 int /*<<< orphan*/  VG_PATH_DATATYPE_S_32 ; 
 int /*<<< orphan*/  VG_PATH_FORMAT_STANDARD ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vgCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDestroyPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDrawPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vgGetError () ; 
 int /*<<< orphan*/  vgSetPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgSetParameterfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vguPolygon (int /*<<< orphan*/ ,int*,int,int) ; 

VCOS_STATUS_T gx_render_arrowhead(GRAPHICS_RESOURCE_HANDLE res,
                                  uint32_t tip_x, uint32_t tip_y,
                                  int32_t w, int32_t h,
                                  GX_PAINT_T *p)
{
   VGfloat gradient[4];
   VGPaint paint = (VGPaint)p;
   VGPath path;
   VCOS_STATUS_T status = VCOS_SUCCESS;

   GX_CLIENT_STATE_T save;
   gx_priv_save(&save, res);

   if (!paint)
   {
      vcos_assert(0);
      status = VCOS_EINVAL;
      goto finish;
   }

   gradient[0] = 0.0; gradient[1] = 0.0;
   gradient[2] = w; gradient[2] = 0.0;

   vgSetParameterfv(paint, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
   vgSetPaint(paint, VG_FILL_PATH);

   path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
                       1.0, 0.0, 8, 8, VG_PATH_CAPABILITY_ALL);
   if (!path)
   {
      status = VCOS_ENOMEM;
      goto finish;
   }
   VGfloat points[] = {
      (VGfloat)tip_x, (VGfloat)tip_y,
      (VGfloat)tip_x + w, (VGfloat)tip_y + h/2,
      (VGfloat)tip_x + w, (VGfloat)tip_y - h/2,
   };

   vguPolygon(path, points, 3, 1);

   vgDrawPath(path, VG_FILL_PATH);
   vgDestroyPath(path);

   vcos_assert(vgGetError()==0);

finish:
   gx_priv_restore(&save);
   return status;
}