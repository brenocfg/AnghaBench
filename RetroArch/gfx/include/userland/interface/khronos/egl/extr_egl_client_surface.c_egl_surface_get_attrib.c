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
struct TYPE_4__ {int height; int largest_pbuffer; int mipmap_texture; int mipmap_level; int swap_behavior; int multisample_resolve; int texture_format; int texture_target; int width; int /*<<< orphan*/  type; int /*<<< orphan*/  config; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  alphaformat; } ;
typedef  int EGLint ;
typedef  TYPE_1__ EGL_SURFACE_T ;
typedef  int /*<<< orphan*/  EGLBoolean ;

/* Variables and functions */
#define  EGL_CONFIG_ID 143 
 int EGL_DISPLAY_SCALING ; 
 int /*<<< orphan*/  EGL_FALSE ; 
#define  EGL_HEIGHT 142 
#define  EGL_HORIZONTAL_RESOLUTION 141 
#define  EGL_LARGEST_PBUFFER 140 
#define  EGL_MIPMAP_LEVEL 139 
#define  EGL_MIPMAP_TEXTURE 138 
#define  EGL_MULTISAMPLE_RESOLVE 137 
#define  EGL_PIXEL_ASPECT_RATIO 136 
#define  EGL_RENDER_BUFFER 135 
#define  EGL_SWAP_BEHAVIOR 134 
#define  EGL_TEXTURE_FORMAT 133 
#define  EGL_TEXTURE_TARGET 132 
 int /*<<< orphan*/  EGL_TRUE ; 
 int EGL_UNKNOWN ; 
#define  EGL_VERTICAL_RESOLUTION 131 
#define  EGL_VG_ALPHA_FORMAT 130 
 int EGL_VG_ALPHA_FORMAT_NONPRE ; 
 int EGL_VG_ALPHA_FORMAT_PRE ; 
#define  EGL_VG_COLORSPACE 129 
 int EGL_VG_COLORSPACE_LINEAR ; 
 int EGL_VG_COLORSPACE_sRGB ; 
#define  EGL_WIDTH 128 
 int /*<<< orphan*/  NONPRE ; 
 int /*<<< orphan*/  PBUFFER ; 
 int /*<<< orphan*/  SRGB ; 
 int egl_surface_get_render_buffer (TYPE_1__*) ; 

EGLBoolean egl_surface_get_attrib(EGL_SURFACE_T *surface, EGLint attrib, EGLint *value)
{
   switch (attrib) {
   case EGL_VG_ALPHA_FORMAT:
      if (surface->alphaformat == NONPRE)
         *value = EGL_VG_ALPHA_FORMAT_NONPRE;
      else
         *value = EGL_VG_ALPHA_FORMAT_PRE;
      return EGL_TRUE;
   case EGL_VG_COLORSPACE:
      if (surface->colorspace == SRGB)
         *value = EGL_VG_COLORSPACE_sRGB;
      else
         *value = EGL_VG_COLORSPACE_LINEAR;
      return EGL_TRUE;
   case EGL_CONFIG_ID:
      *value = (EGLint)(size_t)surface->config;
      return EGL_TRUE;
   case EGL_HEIGHT:
      *value = surface->height;
      return EGL_TRUE;
   case EGL_HORIZONTAL_RESOLUTION:
   case EGL_VERTICAL_RESOLUTION:
      *value = EGL_UNKNOWN;
      return EGL_TRUE;
   case EGL_LARGEST_PBUFFER:
      // For a window or pixmap surface, the contents of value are not modified.
      if (surface->type == PBUFFER)
         *value = surface->largest_pbuffer;
      return EGL_TRUE;
   case EGL_MIPMAP_TEXTURE:
      // Querying EGL_MIPMAP_TEXTURE for a non-pbuffer surface is not
      // an error, but value is not modified.
      if (surface->type == PBUFFER)
         *value = surface->mipmap_texture;
      return EGL_TRUE;
   case EGL_MIPMAP_LEVEL:
      // Querying EGL_MIPMAP_LEVEL for a non-pbuffer surface is not
      // an error, but value is not modified.
      if (surface->type == PBUFFER)
         *value = surface->mipmap_level;
      return EGL_TRUE;
   case EGL_PIXEL_ASPECT_RATIO:
      *value = EGL_DISPLAY_SCALING;
      return EGL_TRUE;
   case EGL_RENDER_BUFFER:
      *value = egl_surface_get_render_buffer(surface);
      return EGL_TRUE;
   case EGL_SWAP_BEHAVIOR:
      *value = surface->swap_behavior;
      return EGL_TRUE;
   case EGL_MULTISAMPLE_RESOLVE:
      *value = surface->multisample_resolve;
      return EGL_TRUE;
   case EGL_TEXTURE_FORMAT:
      // Querying EGL_TEXTURE_FORMAT for a non-pbuffer surface is not
      // an error, but value is not modified.
      if (surface->type == PBUFFER)
         *value = surface->texture_format;
      return EGL_TRUE;
   case EGL_TEXTURE_TARGET:
      // Querying EGL_TEXTURE_TARGET for a non-pbuffer surface is not
      // an error, but value is not modified.
      if (surface->type == PBUFFER)
         *value = surface->texture_target;
      return EGL_TRUE;
   case EGL_WIDTH:
      *value = surface->width;
      return EGL_TRUE;
   default:
      return EGL_FALSE;
   }
}