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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int core_hw_context_enable; } ;
typedef  TYPE_1__ gfx_ctx_drm_data_t ;

/* Variables and functions */
 scalar_t__ BIT32_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFX_CTX_FLAGS_GL_CORE_CONTEXT ; 

__attribute__((used)) static void gfx_ctx_drm_set_flags(void *data, uint32_t flags)
{
   gfx_ctx_drm_data_t *drm     = (gfx_ctx_drm_data_t*)data;
   if (BIT32_GET(flags, GFX_CTX_FLAGS_GL_CORE_CONTEXT))
      drm->core_hw_context_enable = true;
}