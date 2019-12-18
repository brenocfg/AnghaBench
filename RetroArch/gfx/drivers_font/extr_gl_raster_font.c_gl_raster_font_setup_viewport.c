#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* gl; int /*<<< orphan*/  tex; } ;
typedef  TYPE_2__ gl_raster_t ;
struct TYPE_7__ {int /*<<< orphan*/  shader_data; TYPE_1__* shader; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* use ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_FUNC_ADD ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  VIDEO_SHADER_STOCK_BLEND ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendEquation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_driver_set_viewport (unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static void gl_raster_font_setup_viewport(unsigned width, unsigned height,
      gl_raster_t *font, bool full_screen)
{
   video_driver_set_viewport(width, height, full_screen, false);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glBlendEquation(GL_FUNC_ADD);

   glBindTexture(GL_TEXTURE_2D, font->tex);

   if (font->gl->shader && font->gl->shader->use)
      font->gl->shader->use(font->gl,
            font->gl->shader_data, VIDEO_SHADER_STOCK_BLEND, true);
}