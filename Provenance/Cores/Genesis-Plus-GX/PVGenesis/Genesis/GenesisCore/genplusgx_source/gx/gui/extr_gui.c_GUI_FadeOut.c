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
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  gxDrawRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxSetScreen () ; 

void GUI_FadeOut()
{
  int alpha = 0;
  while (alpha < 256)
  {
    gxDrawRectangle(0, 0, 640, 480, alpha, (GXColor)BLACK);
    gxSetScreen();
    alpha +=3;
  }
}