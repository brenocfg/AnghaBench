#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fbo_feedback; scalar_t__ fbo_feedback_texture; } ;
typedef  TYPE_1__ gl_t ;
struct TYPE_6__ {int fbo_pass; scalar_t__* fbo; scalar_t__* fbo_texture; } ;
typedef  TYPE_2__ gl2_renderchain_data_t ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  RARCH_GL_FRAMEBUFFER ; 
 scalar_t__ RARCH_GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  gl2_bind_fb (scalar_t__) ; 
 scalar_t__ gl2_check_fb_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_delete_fb (int,scalar_t__*) ; 
 int /*<<< orphan*/  gl2_fb_texture_2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_gen_fb (int,scalar_t__*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 

__attribute__((used)) static bool gl2_create_fbo_targets(gl_t *gl, gl2_renderchain_data_t *chain)
{
   unsigned i;

   glBindTexture(GL_TEXTURE_2D, 0);
   gl2_gen_fb(chain->fbo_pass, chain->fbo);

   for (i = 0; i < (unsigned)chain->fbo_pass; i++)
   {
      GLenum status;

      gl2_bind_fb(chain->fbo[i]);
      gl2_fb_texture_2d(RARCH_GL_FRAMEBUFFER,
            RARCH_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, chain->fbo_texture[i], 0);

      status = gl2_check_fb_status(RARCH_GL_FRAMEBUFFER);
      if (status != RARCH_GL_FRAMEBUFFER_COMPLETE)
         goto error;
   }

   if (gl->fbo_feedback_texture)
   {
      GLenum status;

      gl2_gen_fb(1, &gl->fbo_feedback);
      gl2_bind_fb(gl->fbo_feedback);
      gl2_fb_texture_2d(RARCH_GL_FRAMEBUFFER,
            RARCH_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            gl->fbo_feedback_texture, 0);

      status = gl2_check_fb_status(RARCH_GL_FRAMEBUFFER);
      if (status != RARCH_GL_FRAMEBUFFER_COMPLETE)
         goto error;

      /* Make sure the feedback textures are cleared
       * so we don't feedback noise. */
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   return true;

error:
   gl2_delete_fb(chain->fbo_pass, chain->fbo);
   if (gl->fbo_feedback)
      gl2_delete_fb(1, &gl->fbo_feedback);
   RARCH_ERR("[GL]: Failed to set up frame buffer objects. Multi-pass shading will not work.\n");
   return false;
}