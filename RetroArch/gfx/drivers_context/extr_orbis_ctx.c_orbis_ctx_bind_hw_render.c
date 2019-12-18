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
struct TYPE_2__ {int /*<<< orphan*/  egl; } ;
typedef  TYPE_1__ orbis_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_bind_hw_render (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void orbis_ctx_bind_hw_render(void *data, bool enable)
{
    orbis_ctx_data_t *ctx_orbis = (orbis_ctx_data_t *)data;

#ifdef HAVE_EGL
    egl_bind_hw_render(&ctx_orbis->egl, enable);
#endif
}