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
struct TYPE_2__ {int /*<<< orphan*/  glCtx; } ;
typedef  TYPE_1__ gfx_ctx_cgl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGLFlushDrawable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_ctx_cgl_swap_buffers(void *data, void *data2)
{
   gfx_ctx_cgl_data_t *cgl = (gfx_ctx_cgl_data_t*)data;

   CGLFlushDrawable(cgl->glCtx);
}