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
struct video_fbo_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  RARCH_GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  RARCH_GL_FORMAT32 ; 
 int /*<<< orphan*/  RARCH_GL_FRAMEBUFFER ; 
 scalar_t__ RARCH_GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  RARCH_GL_INTERNAL_FORMAT32 ; 
 int /*<<< orphan*/  RARCH_GL_TEXTURE_TYPE32 ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  gl2_bind_fb (int /*<<< orphan*/ ) ; 
 scalar_t__ gl2_check_fb_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_fb_texture_2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_load_texture_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gl2_recreate_fbo(
      struct video_fbo_rect *fbo_rect,
      GLuint fbo,
      GLuint* texture
      )
{
   gl2_bind_fb(fbo);
   glDeleteTextures(1, texture);
   glGenTextures(1, texture);
   glBindTexture(GL_TEXTURE_2D, *texture);
   gl2_load_texture_image(GL_TEXTURE_2D,
         0, RARCH_GL_INTERNAL_FORMAT32,
         fbo_rect->width,
         fbo_rect->height,
         0, RARCH_GL_TEXTURE_TYPE32,
         RARCH_GL_FORMAT32, NULL);

   gl2_fb_texture_2d(RARCH_GL_FRAMEBUFFER,
         RARCH_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
         *texture, 0);

   if (gl2_check_fb_status(RARCH_GL_FRAMEBUFFER)
         == RARCH_GL_FRAMEBUFFER_COMPLETE)
      return true;

   RARCH_WARN("Failed to reinitialize FBO texture.\n");
   return false;
}