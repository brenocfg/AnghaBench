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

/* Variables and functions */
#define  ABGR_8888_LT 142 
#define  ABGR_8888_RSO 141 
#define  ABGR_8888_TF 140 
#define  ARGB_8888_LT 139 
#define  ARGB_8888_RSO 138 
#define  ARGB_8888_TF 137 
 int EGL_OPENGL_ES2_BIT ; 
 int EGL_OPENGL_ES_BIT ; 
 int EGL_OPENVG_BIT ; 
#define  RGB_565_LT 136 
#define  RGB_565_RSO 135 
#define  RGB_565_TF 134 
#define  XBGR_8888_LT 133 
#define  XBGR_8888_RSO 132 
#define  XBGR_8888_TF 131 
#define  XRGB_8888_LT 130 
#define  XRGB_8888_RSO 129 
#define  XRGB_8888_TF 128 
 int egl_config_get_color_format (int) ; 
 scalar_t__ egl_config_is_lockable (int) ; 

uint32_t egl_config_get_api_support(int id)
{
   /* no configs are api-specific (ie if you can use a config with gl, you can
    * use it with vg too, and vice-versa). however, some configs have color
    * buffer formats that are incompatible with the hardware, and so can't be
    * used with any api. such configs may still be useful eg with the surface
    * locking extension... */

#if EGL_KHR_lock_surface
   /* to reduce confusion, just say no for all lockable configs. this #if can be
    * safely commented out -- the color buffer format check below will catch
    * lockable configs we actually can't use */
   if (egl_config_is_lockable(id)) {
      return 0;
   }
#endif

   switch (egl_config_get_color_format(id)) {
   case ABGR_8888_RSO: case ABGR_8888_TF: case ABGR_8888_LT:
   case XBGR_8888_RSO: case XBGR_8888_TF: case XBGR_8888_LT:
   case ARGB_8888_RSO: case ARGB_8888_TF: case ARGB_8888_LT:
   case XRGB_8888_RSO: case XRGB_8888_TF: case XRGB_8888_LT:
   case RGB_565_RSO: case RGB_565_TF: case RGB_565_LT:
#ifndef NO_OPENVG
      return (uint32_t)(EGL_OPENGL_ES_BIT | EGL_OPENVG_BIT | EGL_OPENGL_ES2_BIT);
#else
      return (uint32_t)(EGL_OPENGL_ES_BIT | EGL_OPENGL_ES2_BIT);
#endif
   default:
      break;
   }
   return 0;
}