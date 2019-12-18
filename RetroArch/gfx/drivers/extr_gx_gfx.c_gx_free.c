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
typedef  int /*<<< orphan*/  gx_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GX_AbortFrame () ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  OSCloseThreadQueue (scalar_t__) ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 int /*<<< orphan*/  VIDEO_SetBlack (int) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ g_video_cond ; 
 int /*<<< orphan*/  gx_free_overlay (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gx_free(void *data)
{
#ifdef HAVE_OVERLAY
   gx_video_t *gx = (gx_video_t*)data;

   gx_free_overlay(gx);
#endif

   GX_DrawDone();
   GX_AbortFrame();
   GX_Flush();
   VIDEO_SetBlack(true);
   VIDEO_Flush();
   VIDEO_WaitVSync();

   if (g_video_cond)
      OSCloseThreadQueue(g_video_cond);
   g_video_cond = 0;

   free(data);
}