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
 int /*<<< orphan*/  GX_CopyDisp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 int /*<<< orphan*/  VIDEO_SetNextFramebuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  gx_input_UpdateMenu () ; 
 size_t whichfb ; 
 int /*<<< orphan*/ * xfb ; 

void gxSetScreen(void)
{
  GX_DrawDone();
  GX_CopyDisp(xfb[whichfb], GX_FALSE);
  GX_Flush();
  VIDEO_SetNextFramebuffer (xfb[whichfb]);
  VIDEO_Flush ();
  VIDEO_WaitVSync ();
  gx_input_UpdateMenu();
}