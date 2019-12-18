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
typedef  int /*<<< orphan*/  gfx_ctx_sdl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdl_ctx_destroy_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdl_ctx_destroy(void *data)
{
   gfx_ctx_sdl_data_t *sdl = (gfx_ctx_sdl_data_t*)data;

   if (!sdl)
      return;

   sdl_ctx_destroy_resources(sdl);
   free(sdl);
}