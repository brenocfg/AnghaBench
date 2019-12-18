#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fbo_feedback_pass; int /*<<< orphan*/  fbo_feedback_texture; scalar_t__ renderchain_data; scalar_t__ fbo_feedback_enable; } ;
typedef  TYPE_1__ gl_t ;
struct TYPE_8__ {int fbo_pass; int /*<<< orphan*/ * fbo_texture; } ;
typedef  TYPE_2__ gl2_renderchain_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  gl2_create_fbo_texture (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl2_create_fbo_textures(gl_t *gl,
      gl2_renderchain_data_t *chain)
{
   int i;

   glGenTextures(chain->fbo_pass, chain->fbo_texture);

   for (i = 0; i < chain->fbo_pass; i++)
      gl2_create_fbo_texture(gl,
            (gl2_renderchain_data_t*)gl->renderchain_data,
            i, chain->fbo_texture[i]);

   if (gl->fbo_feedback_enable)
   {
      glGenTextures(1, &gl->fbo_feedback_texture);
      gl2_create_fbo_texture(gl,
            (gl2_renderchain_data_t*)gl->renderchain_data,
            gl->fbo_feedback_pass, gl->fbo_feedback_texture);
   }

   glBindTexture(GL_TEXTURE_2D, 0);
}