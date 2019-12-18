#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_15__ {int visible; } ;
struct TYPE_17__ {int /*<<< orphan*/  dpy; } ;
struct TYPE_14__ {int /*<<< orphan*/  interval; } ;
struct TYPE_16__ {unsigned int width; unsigned int height; int buffer_scale; int configured; TYPE_1__ cursor; int /*<<< orphan*/  swap_interval; int /*<<< orphan*/  surface; TYPE_9__ input; int /*<<< orphan*/  vk; scalar_t__ zxdg_toplevel; scalar_t__ xdg_toplevel; TYPE_10__ egl; int /*<<< orphan*/  win; scalar_t__ zxdg_shell; scalar_t__ deco_manager; void* deco; int /*<<< orphan*/  zxdg_surface; scalar_t__ xdg_shell; int /*<<< orphan*/  xdg_surface; int /*<<< orphan*/  compositor; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  int /*<<< orphan*/  EGLNativeWindowType ;

/* Variables and functions */
 unsigned int DEFAULT_WINDOWED_HEIGHT ; 
 unsigned int DEFAULT_WINDOWED_WIDTH ; 
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  VULKAN_WSI_WAYLAND ; 
 int /*<<< orphan*/  egl_create_context (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  egl_create_surface (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * egl_fill_attribs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  egl_set_swap_interval (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_wayland_fd (TYPE_9__*) ; 
 int /*<<< orphan*/  gfx_ctx_wl_destroy (void*) ; 
 int /*<<< orphan*/  gfx_ctx_wl_show_mouse (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vulkan_surface_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int wl_api ; 
 int /*<<< orphan*/  wl_compositor_create_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_egl_window_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_surface_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_listener ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdg_shell_listener ; 
 int /*<<< orphan*/  xdg_surface_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ xdg_surface_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_surface_listener ; 
 int /*<<< orphan*/  xdg_toplevel_add_listener (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xdg_toplevel_listener ; 
 int /*<<< orphan*/  xdg_toplevel_set_app_id (scalar_t__,char*) ; 
 int /*<<< orphan*/  xdg_toplevel_set_fullscreen (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_toplevel_set_title (scalar_t__,char*) ; 
 int /*<<< orphan*/  xdg_wm_base_add_listener (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_wm_base_get_xdg_surface (scalar_t__,int /*<<< orphan*/ ) ; 
 void* zxdg_decoration_manager_v1_get_toplevel_decoration (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zxdg_shell_v6_add_listener (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zxdg_shell_v6_get_xdg_surface (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_shell_v6_listener ; 
 int /*<<< orphan*/  zxdg_surface_v6_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ zxdg_surface_v6_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_surface_v6_listener ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_add_listener (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_listener ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_set_app_id (scalar_t__,char*) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_set_fullscreen (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_set_title (scalar_t__,char*) ; 

__attribute__((used)) static bool gfx_ctx_wl_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
#ifdef HAVE_EGL
   EGLint egl_attribs[16];
   EGLint *attr              = egl_fill_attribs(
         (gfx_ctx_wayland_data_t*)data, egl_attribs);
#endif
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   wl->width                  = width  ? width  : DEFAULT_WINDOWED_WIDTH;
   wl->height                 = height ? height : DEFAULT_WINDOWED_HEIGHT;

   wl->surface                = wl_compositor_create_surface(wl->compositor);

   wl_surface_set_buffer_scale(wl->surface, wl->buffer_scale);
   wl_surface_add_listener(wl->surface, &wl_surface_listener, wl);

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         wl->win        = wl_egl_window_create(wl->surface, wl->width * wl->buffer_scale, wl->height * wl->buffer_scale);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   if (wl->xdg_shell)
   {
      wl->xdg_surface = xdg_wm_base_get_xdg_surface(wl->xdg_shell, wl->surface);
      xdg_surface_add_listener(wl->xdg_surface, &xdg_surface_listener, wl);

      wl->xdg_toplevel = xdg_surface_get_toplevel(wl->xdg_surface);
      xdg_toplevel_add_listener(wl->xdg_toplevel, &xdg_toplevel_listener, wl);

      xdg_toplevel_set_app_id(wl->xdg_toplevel, "retroarch");
      xdg_toplevel_set_title(wl->xdg_toplevel, "RetroArch");

      if (wl->deco_manager)
      {
         wl->deco = zxdg_decoration_manager_v1_get_toplevel_decoration(
               wl->deco_manager, wl->xdg_toplevel);
      }

      /* Waiting for xdg_toplevel to be configured before starting to draw */
      wl_surface_commit(wl->surface);
      wl->configured = true;

      while (wl->configured)
         wl_display_dispatch(wl->input.dpy);

      wl_display_roundtrip(wl->input.dpy);
      xdg_wm_base_add_listener(wl->xdg_shell, &xdg_shell_listener, NULL);
   }
   else if (wl->zxdg_shell)
   {
      wl->zxdg_surface = zxdg_shell_v6_get_xdg_surface(wl->zxdg_shell, wl->surface);
      zxdg_surface_v6_add_listener(wl->zxdg_surface, &zxdg_surface_v6_listener, wl);

      wl->zxdg_toplevel = zxdg_surface_v6_get_toplevel(wl->zxdg_surface);
      zxdg_toplevel_v6_add_listener(wl->zxdg_toplevel, &zxdg_toplevel_v6_listener, wl);

      zxdg_toplevel_v6_set_app_id(wl->zxdg_toplevel, "retroarch");
      zxdg_toplevel_v6_set_title(wl->zxdg_toplevel, "RetroArch");

      if (wl->deco_manager)
         wl->deco = zxdg_decoration_manager_v1_get_toplevel_decoration(
               wl->deco_manager, wl->xdg_toplevel);

      /* Waiting for xdg_toplevel to be configured before starting to draw */
      wl_surface_commit(wl->surface);
      wl->configured = true;

      while (wl->configured)
         wl_display_dispatch(wl->input.dpy);

      wl_display_roundtrip(wl->input.dpy);
      zxdg_shell_v6_add_listener(wl->zxdg_shell, &zxdg_shell_v6_listener, NULL);
   }

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL

         if (!egl_create_context(&wl->egl, (attr != egl_attribs) ? egl_attribs : NULL))
         {
            egl_report_error();
            goto error;
         }

         if (!egl_create_surface(&wl->egl, (EGLNativeWindowType)wl->win))
            goto error;
         egl_set_swap_interval(&wl->egl, wl->egl.interval);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   if (fullscreen)
   {
	   if (wl->xdg_toplevel)
		   xdg_toplevel_set_fullscreen(wl->xdg_toplevel, NULL);
	   else if (wl->zxdg_toplevel)
		   zxdg_toplevel_v6_set_fullscreen(wl->zxdg_toplevel, NULL);
	}

   flush_wayland_fd(&wl->input);

   switch (wl_api)
   {
      case GFX_CTX_VULKAN_API:
         wl_display_roundtrip(wl->input.dpy);

#ifdef HAVE_VULKAN
         if (!vulkan_surface_create(&wl->vk, VULKAN_WSI_WAYLAND,
                  wl->input.dpy, wl->surface,
                  wl->width * wl->buffer_scale, wl->height * wl->buffer_scale, wl->swap_interval))
            goto error;
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   if (fullscreen)
   {
      wl->cursor.visible = false;
      gfx_ctx_wl_show_mouse(wl, false);
   }
   else
      wl->cursor.visible = true;

   return true;

error:
   gfx_ctx_wl_destroy(data);
   return false;
}