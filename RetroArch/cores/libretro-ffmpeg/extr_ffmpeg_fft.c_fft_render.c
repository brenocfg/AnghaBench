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
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/ ** stub_matrix4x4 ;
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_6__ {int /*<<< orphan*/  elems; int /*<<< orphan*/  vao; int /*<<< orphan*/  prog; } ;
struct TYPE_5__ {int /*<<< orphan*/  tex; } ;
struct TYPE_7__ {float block_size; scalar_t__ ms_fbo; TYPE_2__ block; TYPE_1__ blur; int /*<<< orphan*/  output_ptr; } ;
typedef  TYPE_3__ fft_t ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CHECK_ERROR () ; 
#define  GL_COLOR_ATTACHMENT0 129 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
#define  GL_DEPTH_STENCIL_ATTACHMENT 128 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT ; 
 int /*<<< orphan*/  MAT_ELEM_4X4 (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ M_HALF_PI ; 
 int M_PI ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlitFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glInvalidateFramebuffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUniform2i (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform4f (int /*<<< orphan*/ ,float,float,float,float) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  matrix_4x4_lookat (int /*<<< orphan*/ ,float*,float*,float*) ; 
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_projection (int /*<<< orphan*/ ,float,float,float,float) ; 
 int /*<<< orphan*/  vec3_add (float*,float*) ; 

void fft_render(fft_t *fft, GLuint backbuffer, unsigned width, unsigned height)
{
   vec3_t eye, center, up;
   stub_matrix4x4 mvp_real;
   math_matrix_4x4 mvp_lookat, mvp, mvp_persp;

   eye[0]               = 0.0f;
   eye[1]               = 80.0f;
   eye[2]               = -60.0f;

   up[0]                = 0.0f;
   up[1]                = 1.0f;
   up[2]                = 0.0f;

   center[0]            = 0.0f;
   center[1]            = 0.0f;
   center[2]            = 1.0f;

   vec3_add(center, eye);

   matrix_4x4_projection(mvp_persp, (float)M_HALF_PI, (float)width / height, 1.0f, 500.0f);
   matrix_4x4_lookat(mvp_lookat, eye, center, up);
   matrix_4x4_multiply(mvp, mvp_lookat, mvp_persp);

   /* Render scene. */
   glBindFramebuffer(GL_FRAMEBUFFER, fft->ms_fbo ? fft->ms_fbo : backbuffer);
   glViewport(0, 0, width, height);
   glClearColor(0.1f, 0.15f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   glUseProgram(fft->block.prog);

   mvp_real[0][0] = MAT_ELEM_4X4(mvp, 0, 0);
   mvp_real[0][1] = MAT_ELEM_4X4(mvp, 0, 1);
   mvp_real[0][2] = MAT_ELEM_4X4(mvp, 0, 2);
   mvp_real[0][3] = MAT_ELEM_4X4(mvp, 0, 3);
   mvp_real[1][0] = MAT_ELEM_4X4(mvp, 1, 0);
   mvp_real[1][1] = MAT_ELEM_4X4(mvp, 1, 1);
   mvp_real[1][2] = MAT_ELEM_4X4(mvp, 1, 2);
   mvp_real[1][3] = MAT_ELEM_4X4(mvp, 1, 3);
   mvp_real[2][0] = MAT_ELEM_4X4(mvp, 2, 0);
   mvp_real[2][1] = MAT_ELEM_4X4(mvp, 2, 1);
   mvp_real[2][2] = MAT_ELEM_4X4(mvp, 2, 2);
   mvp_real[2][3] = MAT_ELEM_4X4(mvp, 2, 3);
   mvp_real[3][0] = MAT_ELEM_4X4(mvp, 3, 0);
   mvp_real[3][1] = MAT_ELEM_4X4(mvp, 3, 1);
   mvp_real[3][2] = MAT_ELEM_4X4(mvp, 3, 2);
   mvp_real[3][3] = MAT_ELEM_4X4(mvp, 3, 3);

   glUniformMatrix4fv(glGetUniformLocation(fft->block.prog, "uMVP"),
         1, GL_FALSE, (&mvp_real[0][0]));

   glUniform2i(glGetUniformLocation(fft->block.prog, "uOffset"),
         ((-(int)(fft->block_size)) + 1) / 2, fft->output_ptr);
   glUniform4f(glGetUniformLocation(fft->block.prog, "uHeightmapParams"),
         -(fft->block_size - 1.0f) / 2.0f, 0.0f, 3.0f, 2.0f);
   glUniform1f(glGetUniformLocation(fft->block.prog, "uAngleScale"),
         M_PI / ((fft->block_size - 1) / 2));

   glBindVertexArray(fft->block.vao);
   glBindTexture(GL_TEXTURE_2D, fft->blur.tex);
   glDrawElements(GL_TRIANGLE_STRIP, fft->block.elems, GL_UNSIGNED_INT, NULL);
   glBindVertexArray(0);
   glUseProgram(0);

   if (fft->ms_fbo)
   {
      static const GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT };

      glBindFramebuffer(GL_READ_FRAMEBUFFER, fft->ms_fbo);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, backbuffer);
      glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
            GL_COLOR_BUFFER_BIT, GL_NEAREST);

      glBindFramebuffer(GL_FRAMEBUFFER, fft->ms_fbo);
      glInvalidateFramebuffer(GL_FRAMEBUFFER, 2, attachments);
      GL_CHECK_ERROR();
   }

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   GL_CHECK_ERROR();
}