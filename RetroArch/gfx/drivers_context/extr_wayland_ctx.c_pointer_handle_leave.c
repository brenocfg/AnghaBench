#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct TYPE_4__ {int focus; } ;
struct TYPE_5__ {TYPE_1__ mouse; } ;
struct TYPE_6__ {TYPE_2__ input; } ;
typedef  TYPE_3__ gfx_ctx_wayland_data_t ;

/* Variables and functions */

__attribute__((used)) static void pointer_handle_leave(void *data,
      struct wl_pointer *pointer,
      uint32_t serial,
      struct wl_surface *surface)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;
   wl->input.mouse.focus      = false;
   (void)pointer;
   (void)serial;
   (void)surface;
}