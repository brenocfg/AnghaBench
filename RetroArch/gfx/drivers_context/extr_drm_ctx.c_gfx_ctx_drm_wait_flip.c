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
 int /*<<< orphan*/  drm_wait_flip (int) ; 
 int /*<<< orphan*/  g_bo ; 
 int /*<<< orphan*/  g_gbm_surface ; 
 int /*<<< orphan*/  g_next_bo ; 
 int /*<<< orphan*/  gbm_surface_release_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waiting_for_flip ; 

__attribute__((used)) static bool gfx_ctx_drm_wait_flip(bool block)
{
   int timeout = 0;

   if (!waiting_for_flip)
      return false;

   if (block)
      timeout = -1;

   while (waiting_for_flip)
   {
      if (!drm_wait_flip(timeout))
         break;
   }

   if (waiting_for_flip)
      return true;

   /* Page flip has taken place. */

   /* This buffer is not on-screen anymore. Release it to GBM. */
   gbm_surface_release_buffer(g_gbm_surface, g_bo);
   /* This buffer is being shown now. */
   g_bo = g_next_bo;

   return false;
}