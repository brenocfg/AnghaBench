#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int height; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glScissor (int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scissor_set_rectangle (int,unsigned int,int,unsigned int,int) ; 

__attribute__((used)) static void menu_display_gl_scissor_begin(
      video_frame_info_t *video_info, int x, int y,
      unsigned width, unsigned height)
{
   glScissor(x, video_info->height - y - height, width, height);
   glEnable(GL_SCISSOR_TEST);
#ifdef MALI_BUG
   /* TODO/FIXME: If video width/height changes between
    * a call of menu_display_gl_scissor_begin() and the
    * next call of menu_display_gl_draw() (or if
    * menu_display_gl_scissor_begin() is called before the
    * first call of menu_display_gl_draw()), the scissor
    * rectangle set here will be overwritten by the initialisation
    * procedure inside menu_display_gl_discard_draw_rectangle(),
    * causing the next frame to render glitched content */
   scissor_set_rectangle(x, x + width - 1, y, y + height - 1, 1);
#endif
}