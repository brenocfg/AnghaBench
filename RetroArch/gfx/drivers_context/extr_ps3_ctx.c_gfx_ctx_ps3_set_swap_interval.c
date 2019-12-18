#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  GL_VSYNC_SCE ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_ctx_ps3_set_swap_interval(void *data, int interval)
{
#if defined(HAVE_PSGL)
   if (interval == 1)
      glEnable(GL_VSYNC_SCE);
   else
      glDisable(GL_VSYNC_SCE);
#endif
}