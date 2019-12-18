#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  double VGfloat ;
typedef  int /*<<< orphan*/  VGPath ;
typedef  int /*<<< orphan*/  VGPaint ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; } ;
typedef  int /*<<< orphan*/  GX_PAINT_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  TYPE_1__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ GRAPHICS_RESOURCE_HEIGHT ; 
 scalar_t__ GRAPHICS_RESOURCE_WIDTH ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_FILL_PATH ; 
 int /*<<< orphan*/  VG_PAINT_LINEAR_GRADIENT ; 
 int /*<<< orphan*/  VG_PATH_CAPABILITY_ALL ; 
 int /*<<< orphan*/  VG_PATH_DATATYPE_S_32 ; 
 int /*<<< orphan*/  VG_PATH_FORMAT_STANDARD ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vgCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDestroyPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDrawPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vgGetError () ; 
 int /*<<< orphan*/  vgSetPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgSetParameterfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  vguRoundRect (int /*<<< orphan*/ ,double,double,double,double,double,double) ; 

VCOS_STATUS_T gx_fill_gradient(GRAPHICS_RESOURCE_HANDLE dest,
                               uint32_t x, uint32_t y,
                               uint32_t width, uint32_t height,
                               uint32_t radius,
                               GX_PAINT_T *p)
{
   /* Define start and end points of gradient, see OpenVG specification,
      section 9.3.3. */
   VGfloat gradient[4] = {0.0, 0.0, 0.0, 0.0};
   VGPaint paint = (VGPaint)p;
   VGPath path;
   GX_CLIENT_STATE_T save;
   VCOS_STATUS_T status = VCOS_SUCCESS;

   if (!paint)
      return VCOS_EINVAL;

   gx_priv_save(&save, dest);

   if (width == GRAPHICS_RESOURCE_WIDTH)
      width = dest->width;

   if (height == GRAPHICS_RESOURCE_HEIGHT)
      height = dest->height;

   gradient[2] = width;

   vgSetParameterfv(paint, VG_PAINT_LINEAR_GRADIENT, 4, gradient);
   vgSetPaint(paint, VG_FILL_PATH);

   path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
                       1.0, 0.0, 8, 8, VG_PATH_CAPABILITY_ALL);
   if (!path)
   {
      status = VCOS_ENOMEM;
      goto finish;
   }

   vguRoundRect(path, (VGfloat)x, (VGfloat)y, (VGfloat)width, (VGfloat)height,
                (VGfloat)radius, (VGfloat)radius);
   vgDrawPath(path, VG_FILL_PATH);
   vgDestroyPath(path);

   vcos_assert(vgGetError() == 0);

finish:
   gx_priv_restore(&save);

   return status;
}