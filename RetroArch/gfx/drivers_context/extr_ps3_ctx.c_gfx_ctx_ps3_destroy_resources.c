#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gl_device; int /*<<< orphan*/  gl_context; } ;
typedef  TYPE_1__ gfx_ctx_ps3_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  psglDestroyContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psglDestroyDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psglExit () ; 

__attribute__((used)) static void gfx_ctx_ps3_destroy_resources(gfx_ctx_ps3_data_t *ps3)
{
   if (!ps3)
      return;

#if defined(HAVE_PSGL)
   psglDestroyContext(ps3->gl_context);
   psglDestroyDevice(ps3->gl_device);

   psglExit();
#endif
}