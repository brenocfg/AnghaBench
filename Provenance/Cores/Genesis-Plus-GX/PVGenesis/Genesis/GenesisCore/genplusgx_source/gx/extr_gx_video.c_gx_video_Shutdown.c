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
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  FONT_Shutdown () ; 
 int /*<<< orphan*/  VIDEO_ClearFrameBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ screenshot ; 
 scalar_t__ texturemem ; 
 int /*<<< orphan*/  vmode ; 
 size_t whichfb ; 
 int /*<<< orphan*/ * xfb ; 

void gx_video_Shutdown(void)
{
  if (texturemem) free(texturemem);
  if (screenshot) free(screenshot);
  FONT_Shutdown();
  VIDEO_ClearFrameBuffer(vmode, xfb[whichfb], COLOR_BLACK);
  VIDEO_Flush();
  VIDEO_WaitVSync();
}