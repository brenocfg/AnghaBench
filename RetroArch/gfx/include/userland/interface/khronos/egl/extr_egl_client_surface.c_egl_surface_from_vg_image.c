#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ VGImage ;
struct TYPE_5__ {int swap_interval; int server_owned; int is_destroyed; int is_locked; int buffers; int avail_buffers_valid; int /*<<< orphan*/  alphaformat; int /*<<< orphan*/  colorspace; scalar_t__ height; scalar_t__ width; scalar_t__ serverbuffer; scalar_t__ mapped_buffer; scalar_t__ context_binding_count; scalar_t__* pixmap_server_handle; scalar_t__ pixmap; void* texture_target; void* texture_format; scalar_t__ mipmap_level; scalar_t__ mipmap_texture; scalar_t__ largest_pbuffer; scalar_t__ win; scalar_t__ config; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ KHRN_IMAGE_FORMAT_T ;
typedef  scalar_t__ EGLint ;
typedef  void* EGLenum ;
typedef  TYPE_1__ EGL_SURFACE_T ;
typedef  int /*<<< orphan*/  EGLSurface ;
typedef  scalar_t__ EGLConfig ;
typedef  scalar_t__ EGLBoolean ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  EGLINTCREATEPBUFFERFROMVGIMAGE_ID ; 
 scalar_t__ EGL_BAD_ALLOC ; 
 int /*<<< orphan*/  EGL_DEPTH_SIZE ; 
 int /*<<< orphan*/  EGL_STENCIL_SIZE ; 
 scalar_t__ EGL_SUCCESS ; 
 scalar_t__ IMAGE_FORMAT_INVALID ; 
 scalar_t__ IMAGE_FORMAT_LIN ; 
 scalar_t__ IMAGE_FORMAT_PRE ; 
 int /*<<< orphan*/  LINEAR ; 
 int /*<<< orphan*/  NONPRE ; 
 int /*<<< orphan*/  PBUFFER ; 
 int /*<<< orphan*/  PRE ; 
 int /*<<< orphan*/  RPC_CALL9_OUT_CTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RPC_UINT (scalar_t__) ; 
 int /*<<< orphan*/  SRGB ; 
 int /*<<< orphan*/  eglIntCreatePbufferFromVGImage_impl ; 
 int /*<<< orphan*/  egl_config_get_attrib (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ egl_config_get_color_format (int) ; 
 scalar_t__ egl_config_get_depth_format (int) ; 
 scalar_t__ egl_config_get_mask_format (int) ; 
 scalar_t__ egl_config_get_multisample_format (int) ; 
 TYPE_1__* egl_surface_pool_alloc () ; 
 int /*<<< orphan*/  egl_surface_pool_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

EGL_SURFACE_T *egl_surface_from_vg_image(
   VGImage vg_handle,
   EGLSurface name,
   EGLConfig config,
   EGLBoolean largest_pbuffer,
   EGLBoolean mipmap_texture,
   EGLenum texture_format,
   EGLenum texture_target,
   EGLint *error)
{
   KHRN_IMAGE_FORMAT_T color;
   KHRN_IMAGE_FORMAT_T depth;
   KHRN_IMAGE_FORMAT_T mask;
   KHRN_IMAGE_FORMAT_T multi;
   EGLint   config_depth_bits;
   EGLint   config_stencil_bits;
   uint32_t results[5];
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

   EGL_SURFACE_T *surface = egl_surface_pool_alloc();

   if (!surface) {
      *error = EGL_BAD_ALLOC;
      return 0;
   }

   /* TODO: respect largest_pbuffer? */

   surface->name = name;
   surface->type = PBUFFER;

   surface->config = config;
   surface->win = 0;
   surface->swap_interval = 1;

   surface->largest_pbuffer = largest_pbuffer;
   surface->mipmap_texture = mipmap_texture;
   surface->mipmap_level = 0;
   surface->texture_format = texture_format;
   surface->texture_target = texture_target;
   surface->pixmap = 0;
   surface->pixmap_server_handle[0] = 0;
   surface->pixmap_server_handle[1] = (uint32_t)-1;
   surface->server_owned = false;

   surface->context_binding_count = 0;
   surface->is_destroyed = false;

#if EGL_KHR_lock_surface
   surface->is_locked = false;
   surface->mapped_buffer = 0;
#endif

   color = egl_config_get_color_format((int)(size_t)config - 1);
   depth = egl_config_get_depth_format((int)(size_t)config - 1);
   mask = egl_config_get_mask_format((int)(size_t)config - 1);
   multi = egl_config_get_multisample_format((int)(size_t)config - 1);

   /* Find depth and stencil bits from chosen config (these may NOT be the same as the underlying format!) */
   egl_config_get_attrib((int)(size_t)config - 1, EGL_DEPTH_SIZE, &config_depth_bits);
   egl_config_get_attrib((int)(size_t)config - 1, EGL_STENCIL_SIZE, &config_stencil_bits);

   vcos_assert(color != IMAGE_FORMAT_INVALID);

   surface->buffers = 1;

   RPC_CALL9_OUT_CTRL(eglIntCreatePbufferFromVGImage_impl,
                     thread,
                     EGLINTCREATEPBUFFERFROMVGIMAGE_ID,
                     RPC_UINT(vg_handle),
                     RPC_UINT(color),
                     RPC_UINT(depth),
                     RPC_UINT(mask),
                     RPC_UINT(multi),
                     RPC_UINT(mipmap_texture),
                     RPC_UINT(config_depth_bits),
                     RPC_UINT(config_stencil_bits),
                     results);

   surface->avail_buffers_valid = false;

   if (results[0]) {
      KHRN_IMAGE_FORMAT_T format = (KHRN_IMAGE_FORMAT_T)results[4];

      surface->serverbuffer = results[0];
      surface->width = results[2];
      surface->height = results[3];

      /* TODO: picking apart image formats like this seems messy */
      surface->colorspace = (format & IMAGE_FORMAT_LIN) ? LINEAR : SRGB;
      surface->alphaformat = (format & IMAGE_FORMAT_PRE) ? PRE : NONPRE;
      *error = EGL_SUCCESS;
      return surface;
   } else {
      *error = results[1];
      egl_surface_pool_free(surface);
      return 0;
   }
}