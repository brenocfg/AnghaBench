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
typedef  TYPE_1__ qnx_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  egl_set_swap_interval (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gfx_ctx_qnx_set_swap_interval(void *data, int swap_interval)
{
   qnx_ctx_data_t *qnx = (qnx_ctx_data_t*)data;

#ifdef HAVE_EGL
   egl_set_swap_interval(&qnx->egl, swap_interval);
#endif
}