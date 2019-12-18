#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ VIDTEX_T ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  VIDTEX_CHECK_GL (TYPE_1__*) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFlush () ; 

__attribute__((used)) static void vidtex_flush_gl(VIDTEX_T *vt)
{
   int i;

   glFlush();
   glClearColor(0, 0, 0, 0);

   for (i = 0; i < 10; i++)
   {
      glClear(GL_COLOR_BUFFER_BIT);
      eglSwapBuffers(vt->display, vt->surface);
      VIDTEX_CHECK_GL(vt);
   }

   glFlush();
   VIDTEX_CHECK_GL(vt);
}