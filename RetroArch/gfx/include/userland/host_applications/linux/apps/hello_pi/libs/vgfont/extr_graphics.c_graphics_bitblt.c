#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
typedef  double VGfloat ;
typedef  scalar_t__ VGPaint ;
typedef  scalar_t__ VGImage ;
struct TYPE_6__ {scalar_t__ pixmap; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ const width; scalar_t__ const height; double alpha; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  TYPE_2__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ const GRAPHICS_RESOURCE_HEIGHT ; 
 scalar_t__ const GRAPHICS_RESOURCE_WIDTH ; 
 int /*<<< orphan*/  GX_LOG (char*,int) ; 
 scalar_t__ GX_PBUFFER ; 
 int /*<<< orphan*/  VG_DRAW_IMAGE_MULTIPLY ; 
 int VG_FILL_PATH ; 
 int /*<<< orphan*/  VG_IMAGE_MODE ; 
 scalar_t__ VG_INVALID_HANDLE ; 
 int /*<<< orphan*/  VG_MATRIX_IMAGE_USER_TO_SURFACE ; 
 int /*<<< orphan*/  VG_MATRIX_MODE ; 
 int /*<<< orphan*/  VG_PAINT_COLOR ; 
 int VG_STROKE_PATH ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vgChildImage (scalar_t__,scalar_t__ const,scalar_t__ const,scalar_t__,scalar_t__) ; 
 scalar_t__ vgCreatePaint () ; 
 int /*<<< orphan*/  vgDestroyImage (scalar_t__) ; 
 int /*<<< orphan*/  vgDestroyPaint (scalar_t__) ; 
 int /*<<< orphan*/  vgDrawImage (scalar_t__) ; 
 int vgGetError () ; 
 int /*<<< orphan*/  vgGetMatrix (double*) ; 
 int /*<<< orphan*/  vgLoadIdentity () ; 
 int /*<<< orphan*/  vgLoadMatrix (double*) ; 
 int /*<<< orphan*/  vgScale (double,double) ; 
 int /*<<< orphan*/  vgSetPaint (scalar_t__,int) ; 
 int /*<<< orphan*/  vgSetParameterfv (scalar_t__,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  vgSeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgTranslate (double,double) ; 

int32_t graphics_bitblt( const GRAPHICS_RESOURCE_HANDLE src,
                         const uint32_t x, // offset within source
                         const uint32_t y, // offset within source
                         const uint32_t width,
                         const uint32_t height,
                         GRAPHICS_RESOURCE_HANDLE dest,
                         const uint32_t x_pos,
                         const uint32_t y_pos )
{
   int rc = -1;
   VGfloat old[9];
   uint32_t w, h;
   VGPaint paint = VG_INVALID_HANDLE;
   GX_CLIENT_STATE_T save;
   int is_child = 0;
   VGImage img = VG_INVALID_HANDLE;

   gx_priv_save(&save, dest);

   if (src->type != GX_PBUFFER)
   {
      vcos_assert(0);
      goto finish;
   }

   // create a child image that contains just the part wanted
   w = width == GRAPHICS_RESOURCE_WIDTH ? src->width : width;
   h = height == GRAPHICS_RESOURCE_HEIGHT ? src->height : height;

   if (x==0 && y==0 &&
       w == src->width &&
       h == src->height)
   {
      img = src->u.pixmap;
   }
   else
   {
      is_child = 1;
      img = vgChildImage(src->u.pixmap, x, y, w, h);
      if (img == VG_INVALID_HANDLE)
      {
         vcos_assert(0);
         goto finish;
      }
   }

   vcos_assert(vgGetError()==0);

   vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
   vgGetMatrix(old);
   vgLoadIdentity();
   vgTranslate((VGfloat)x_pos, (VGfloat)(dest->height-y_pos));
   vgScale(1.0, -1.0);

   // Do we have a translucency going on?
   if (src->alpha != 1.0)
   {
      VGfloat colour[4] = {1.0,1.0,1.0,src->alpha};
      paint = vgCreatePaint();

      vgSetParameterfv(paint, VG_PAINT_COLOR, 4, colour);
      vgSeti(VG_IMAGE_MODE, VG_DRAW_IMAGE_MULTIPLY);
      vgSetPaint(paint, VG_STROKE_PATH | VG_FILL_PATH);
   }
   vcos_assert(vgGetError()==0);

   vgDrawImage(img);
   vcos_assert(vgGetError()==0);
   vgLoadMatrix(old);

   int err = vgGetError();

   if (err)
   {
      GX_LOG("vg error %x blitting area", err);
      vcos_assert(0);
      rc = -1;
   }
   else
   {
      rc = 0;
   }
finish:
   if (paint != VG_INVALID_HANDLE)
      vgDestroyPaint(paint);

   if (is_child)
      vgDestroyImage(img);

   gx_priv_restore(&save);
   return rc;
}