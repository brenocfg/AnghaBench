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
typedef  int /*<<< orphan*/  input_device_driver_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* joypad; } ;
typedef  TYPE_1__ input_ctx_wayland_data_t ;

/* Variables and functions */

__attribute__((used)) static const input_device_driver_t *input_wl_get_joypad_driver(void *data)
{
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;
   if (!wl)
      return NULL;
   return wl->joypad;
}