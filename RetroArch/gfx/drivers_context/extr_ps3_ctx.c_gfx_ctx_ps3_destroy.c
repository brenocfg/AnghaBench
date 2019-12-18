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
typedef  int /*<<< orphan*/  gfx_ctx_ps3_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  gfx_ctx_ps3_destroy_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_ctx_ps3_destroy(void *data)
{
   gfx_ctx_ps3_data_t *ps3 = (gfx_ctx_ps3_data_t*)data;

   if (!ps3)
      return;

   gfx_ctx_ps3_destroy_resources(ps3);
   free(data);
}