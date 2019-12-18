#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {TYPE_1__ vp; } ;
typedef  TYPE_2__ gl_t ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_PACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_PACK_ROW_LENGTH ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  glReadBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl2_renderchain_readback(
      gl_t *gl,
      void *chain_data,
      unsigned alignment,
      unsigned fmt, unsigned type,
      void *src)
{
   glPixelStorei(GL_PACK_ALIGNMENT, alignment);
#ifndef HAVE_OPENGLES
   glPixelStorei(GL_PACK_ROW_LENGTH, 0);
   glReadBuffer(GL_BACK);
#endif

   glReadPixels(gl->vp.x, gl->vp.y,
         gl->vp.width, gl->vp.height,
         (GLenum)fmt, (GLenum)type, (GLvoid*)src);
}