#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * dpy; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * surface; scalar_t__ theme; } ;
struct TYPE_7__ {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * zxdg_toplevel; int /*<<< orphan*/ * xdg_toplevel; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * xdg_surface; TYPE_2__ input; int /*<<< orphan*/ * registry; int /*<<< orphan*/ * compositor; int /*<<< orphan*/ * zxdg_shell; int /*<<< orphan*/ * xdg_shell; int /*<<< orphan*/ * win; scalar_t__ idle_inhibitor; scalar_t__ deco_manager; scalar_t__ deco; scalar_t__ idle_inhibit_manager; scalar_t__ zxdg_surface; scalar_t__ seat; TYPE_1__ cursor; scalar_t__ wl_touch; scalar_t__ wl_pointer; scalar_t__ wl_keyboard; int /*<<< orphan*/  vk; int /*<<< orphan*/  egl; } ;
typedef  TYPE_3__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_xkb () ; 
 int /*<<< orphan*/  vulkan_context_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wl_api ; 
 int /*<<< orphan*/  wl_compositor_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_egl_window_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_keyboard_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_pointer_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_registry_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_seat_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_touch_destroy (scalar_t__) ; 
 int /*<<< orphan*/  xdg_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_toplevel_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_wm_base_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zwp_idle_inhibit_manager_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zwp_idle_inhibitor_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zxdg_decoration_manager_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zxdg_shell_v6_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zxdg_surface_v6_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zxdg_toplevel_decoration_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_ctx_wl_destroy_resources(gfx_ctx_wayland_data_t *wl)
{
   if (!wl)
      return;

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         egl_destroy(&wl->egl);

         if (wl->win)
            wl_egl_window_destroy(wl->win);
#endif
         break;
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         vulkan_context_destroy(&wl->vk, wl->surface);

         if (wl->input.dpy != NULL && wl->input.fd >= 0)
            close(wl->input.fd);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

#ifdef HAVE_XKBCOMMON
   free_xkb();
#endif

   if (wl->wl_keyboard)
      wl_keyboard_destroy(wl->wl_keyboard);
   if (wl->wl_pointer)
      wl_pointer_destroy(wl->wl_pointer);
   if (wl->wl_touch)
      wl_touch_destroy(wl->wl_touch);

   if (wl->cursor.theme)
      wl_cursor_theme_destroy(wl->cursor.theme);
   if (wl->cursor.surface)
      wl_surface_destroy(wl->cursor.surface);

   if (wl->seat)
      wl_seat_destroy(wl->seat);
   if (wl->xdg_shell)
      xdg_wm_base_destroy(wl->xdg_shell);
   if (wl->zxdg_shell)
      zxdg_shell_v6_destroy(wl->zxdg_shell);
   if (wl->compositor)
      wl_compositor_destroy(wl->compositor);
   if (wl->registry)
      wl_registry_destroy(wl->registry);
   if (wl->xdg_surface)
      xdg_surface_destroy(wl->xdg_surface);
   if (wl->zxdg_surface)
      zxdg_surface_v6_destroy(wl->zxdg_surface);
   if (wl->surface)
      wl_surface_destroy(wl->surface);
   if (wl->xdg_toplevel)
      xdg_toplevel_destroy(wl->xdg_toplevel);
   if (wl->zxdg_toplevel)
      zxdg_toplevel_v6_destroy(wl->zxdg_toplevel);
   if (wl->idle_inhibit_manager)
      zwp_idle_inhibit_manager_v1_destroy(wl->idle_inhibit_manager);
   if (wl->deco)
      zxdg_toplevel_decoration_v1_destroy(wl->deco);
   if (wl->deco_manager)
      zxdg_decoration_manager_v1_destroy(wl->deco_manager);
   if (wl->idle_inhibitor)
      zwp_idle_inhibitor_v1_destroy(wl->idle_inhibitor);

   if (wl->input.dpy)
   {
      wl_display_flush(wl->input.dpy);
      wl_display_disconnect(wl->input.dpy);
   }

#ifdef HAVE_EGL
   wl->win              = NULL;
#endif
   wl->xdg_shell        = NULL;
   wl->zxdg_shell       = NULL;
   wl->compositor       = NULL;
   wl->registry         = NULL;
   wl->input.dpy        = NULL;
   wl->xdg_surface      = NULL;
   wl->surface          = NULL;
   wl->xdg_toplevel     = NULL;
   wl->zxdg_toplevel    = NULL;

   wl->width            = 0;
   wl->height           = 0;

}