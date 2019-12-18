#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  surf; int /*<<< orphan*/  dpy; } ;
struct TYPE_4__ {TYPE_1__ egl; void** eglBuffer; scalar_t__* vgimage; int /*<<< orphan*/  eglimage_ctx; int /*<<< orphan*/  res; int /*<<< orphan*/  pbuff_surf; } ;
typedef  TYPE_2__ vc_ctx_data_t ;
typedef  int /*<<< orphan*/  EGLClientBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_OPENVG_API ; 
 int /*<<< orphan*/  EGL_VG_PARENT_IMAGE_KHR ; 
 unsigned int MAX_EGLIMAGE_TEXTURES ; 
 int /*<<< orphan*/  VG_IMAGE_QUALITY_NONANTIALIASED ; 
 int /*<<< orphan*/  VG_sRGB_565 ; 
 int /*<<< orphan*/  VG_sXRGB_8888 ; 
 int /*<<< orphan*/  eglBindAPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_ctx_vc_bind_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* peglCreateImageKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_api ; 
 scalar_t__ vgCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgImageSubData (scalar_t__,void const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static bool gfx_ctx_vc_image_buffer_write(void *data, const void *frame, unsigned width,
      unsigned height, unsigned pitch, bool rgb32, unsigned index, void **image_handle)
{
   bool ret = false;
   vc_ctx_data_t *vc = (vc_ctx_data_t*)data;

   if (!vc || index >= MAX_EGLIMAGE_TEXTURES)
      goto error;

   eglBindAPI(EGL_OPENVG_API);
   eglMakeCurrent(vc->egl.dpy, vc->pbuff_surf, vc->pbuff_surf, vc->eglimage_ctx);

   if (!vc->eglBuffer[index] || !vc->vgimage[index])
   {
      vc->vgimage[index] = vgCreateImage(
            rgb32 ? VG_sXRGB_8888 : VG_sRGB_565,
            vc->res,
            vc->res,
            VG_IMAGE_QUALITY_NONANTIALIASED);
      vc->eglBuffer[index] = peglCreateImageKHR(
            vc->egl.dpy,
            vc->eglimage_ctx,
            EGL_VG_PARENT_IMAGE_KHR,
            (EGLClientBuffer)vc->vgimage[index],
            NULL);
      ret = true;
   }

   vgImageSubData(
         vc->vgimage[index],
         frame, pitch,
         (rgb32 ? VG_sXRGB_8888 : VG_sRGB_565),
         0,
         0,
         width,
         height);
   *image_handle = vc->eglBuffer[index];

   gfx_ctx_vc_bind_api(NULL, vc_api, 0, 0);
   eglMakeCurrent(vc->egl.dpy, vc->egl.surf, vc->egl.surf, vc->egl.ctx);

   return ret;

error:
   *image_handle = NULL;
   return false;
}