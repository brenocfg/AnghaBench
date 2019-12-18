#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct zxdg_shell_v6 {int dummy; } ;
struct zxdg_decoration_manager_v1 {int dummy; } ;
struct zwp_idle_inhibit_manager_v1 {int dummy; } ;
struct xdg_wm_base {int dummy; } ;
struct wl_shm {int dummy; } ;
struct wl_seat {int dummy; } ;
struct wl_registry {int dummy; } ;
struct wl_output {int dummy; } ;
struct wl_compositor {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; struct wl_output* output; int /*<<< orphan*/  global_id; } ;
typedef  TYPE_2__ output_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  dpy; } ;
struct TYPE_8__ {struct zxdg_decoration_manager_v1* deco_manager; struct zwp_idle_inhibit_manager_v1* idle_inhibit_manager; struct wl_seat* seat; struct wl_shm* shm; struct zxdg_shell_v6* zxdg_shell; struct xdg_wm_base* xdg_shell; TYPE_1__ input; int /*<<< orphan*/  all_outputs; struct wl_compositor* compositor; } ;
typedef  TYPE_3__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  output_listener ; 
 int /*<<< orphan*/  seat_listener ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  wl_compositor_interface ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_output_add_listener (struct wl_output*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  wl_output_interface ; 
 scalar_t__ wl_registry_bind (struct wl_registry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl_seat_add_listener (struct wl_seat*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wl_seat_interface ; 
 int /*<<< orphan*/  wl_shm_interface ; 
 int /*<<< orphan*/  xdg_wm_base_interface ; 
 int /*<<< orphan*/  zwp_idle_inhibit_manager_v1_interface ; 
 int /*<<< orphan*/  zxdg_decoration_manager_v1_interface ; 
 int /*<<< orphan*/  zxdg_shell_v6_interface ; 

__attribute__((used)) static void registry_handle_global(void *data, struct wl_registry *reg,
      uint32_t id, const char *interface, uint32_t version)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   (void)version;

   if (string_is_equal(interface, "wl_compositor"))
      wl->compositor = (struct wl_compositor*)wl_registry_bind(reg,
            id, &wl_compositor_interface, 3);
   else if (string_is_equal(interface, "wl_output"))
   {
      output_info_t *oi = (output_info_t*)
         calloc(1, sizeof(output_info_t));

      oi->global_id     = id;
      oi->output        = (struct wl_output*)wl_registry_bind(reg,
            id, &wl_output_interface, 2);
      wl_output_add_listener(oi->output, &output_listener, oi);
      wl_list_insert(&wl->all_outputs, &oi->link);
      wl_display_roundtrip(wl->input.dpy);
   }
   else if (string_is_equal(interface, "xdg_wm_base"))
      wl->xdg_shell = (struct xdg_wm_base*)
         wl_registry_bind(reg, id, &xdg_wm_base_interface, 1);
   else if (string_is_equal(interface, "zxdg_shell_v6"))
      wl->zxdg_shell = (struct zxdg_shell_v6*)
         wl_registry_bind(reg, id, &zxdg_shell_v6_interface, 1);
   else if (string_is_equal(interface, "wl_shm"))
      wl->shm = (struct wl_shm*)wl_registry_bind(reg, id, &wl_shm_interface, 1);
   else if (string_is_equal(interface, "wl_seat"))
   {
      wl->seat = (struct wl_seat*)wl_registry_bind(reg, id, &wl_seat_interface, 2);
      wl_seat_add_listener(wl->seat, &seat_listener, wl);
   }
   else if (string_is_equal(interface, "zwp_idle_inhibit_manager_v1"))
      wl->idle_inhibit_manager = (struct zwp_idle_inhibit_manager_v1*)wl_registry_bind(
                                  reg, id, &zwp_idle_inhibit_manager_v1_interface, 1);
   else if (string_is_equal(interface, "zxdg_decoration_manager_v1"))
      wl->deco_manager = (struct zxdg_decoration_manager_v1*)wl_registry_bind(
                                  reg, id, &zxdg_decoration_manager_v1_interface, 1);
}