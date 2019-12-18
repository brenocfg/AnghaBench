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
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int IsFullscreen ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int outputheight ; 
 unsigned int outputwidth ; 

void VIDSoftResize(unsigned int w, unsigned int h, int on)
{
#ifdef USE_OPENGL
   IsFullscreen = on;
   glClear(GL_COLOR_BUFFER_BIT);
   glViewport(0, 0, w, h);
   outputwidth = w;
   outputheight = h;
#endif
}