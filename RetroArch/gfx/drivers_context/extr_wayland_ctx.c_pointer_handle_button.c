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
typedef  scalar_t__ uint32_t ;
struct wl_pointer {int dummy; } ;
struct TYPE_4__ {int left; int right; int middle; } ;
struct TYPE_5__ {TYPE_1__ mouse; int /*<<< orphan*/  key_state; } ;
struct TYPE_6__ {TYPE_2__ input; int /*<<< orphan*/  seat; scalar_t__ zxdg_toplevel; scalar_t__ xdg_toplevel; } ;
typedef  TYPE_3__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 scalar_t__ BIT_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTN_LEFT ; 
 scalar_t__ BTN_MIDDLE ; 
 scalar_t__ BTN_RIGHT ; 
 int /*<<< orphan*/  KEY_LEFTALT ; 
 scalar_t__ WL_POINTER_BUTTON_STATE_PRESSED ; 
 int /*<<< orphan*/  xdg_toplevel_move (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zxdg_toplevel_v6_move (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pointer_handle_button(void *data,
      struct wl_pointer *wl_pointer,
      uint32_t serial,
      uint32_t time,
      uint32_t button,
      uint32_t state)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   if (state == WL_POINTER_BUTTON_STATE_PRESSED)
   {
      if (button == BTN_LEFT)
      {
         wl->input.mouse.left = true;

         if (BIT_GET(wl->input.key_state, KEY_LEFTALT))
         {
			 if (wl->xdg_toplevel)
			   xdg_toplevel_move(wl->xdg_toplevel, wl->seat, serial);
			 else if (wl->zxdg_toplevel)
			   zxdg_toplevel_v6_move(wl->zxdg_toplevel, wl->seat, serial);
         }
      }
      else if (button == BTN_RIGHT)
         wl->input.mouse.right = true;
      else if (button == BTN_MIDDLE)
         wl->input.mouse.middle = true;
   }
   else
   {
      if (button == BTN_LEFT)
         wl->input.mouse.left = false;
      else if (button == BTN_RIGHT)
         wl->input.mouse.right = false;
      else if (button == BTN_MIDDLE)
         wl->input.mouse.middle = false;
   }
}