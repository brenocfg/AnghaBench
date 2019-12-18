#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zxdg_toplevel_v6 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  key_state; } ;
struct TYPE_4__ {TYPE_1__ input; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_ESC ; 

__attribute__((used)) static void handle_zxdg_toplevel_close(void *data,
      struct zxdg_toplevel_v6 *zxdg_toplevel)
{
	gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;
	BIT_SET(wl->input.key_state, KEY_ESC);
}