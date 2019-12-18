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
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  GX_CopyDisp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_SetCopyClear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int whichfb ; 
 int /*<<< orphan*/ * xfb ; 

void gxClearScreen(GXColor color)
{
  whichfb ^= 1;
  GX_SetCopyClear(color,0x00ffffff);
  GX_CopyDisp(xfb[whichfb], GX_TRUE);
  GX_Flush();
}