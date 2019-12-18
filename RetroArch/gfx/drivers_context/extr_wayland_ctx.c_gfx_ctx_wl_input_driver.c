#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_driver_t ;
struct TYPE_2__ {int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_wayland ; 
 int /*<<< orphan*/  input_wl_init (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void gfx_ctx_wl_input_driver(void *data,
      const char *joypad_name,
      input_driver_t **input, void **input_data)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;
   /* Input is heavily tied to the window stuff
    * on Wayland, so just implement the input driver here. */
   if (!input_wl_init(&wl->input, joypad_name))
   {
      *input      = NULL;
      *input_data = NULL;
   }
   else
   {
      *input      = &input_wayland;
      *input_data = &wl->input;
   }
}