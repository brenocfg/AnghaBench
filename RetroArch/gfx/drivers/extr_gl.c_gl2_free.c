#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int textures; scalar_t__ renderchain_data; scalar_t__ core_context_in_use; int /*<<< orphan*/  pbo_readback_scaler; int /*<<< orphan*/ * pbo_readback; scalar_t__ pbo_readback_enable; int /*<<< orphan*/  scaler; int /*<<< orphan*/  pbo; scalar_t__ menu_texture; scalar_t__* texture; int /*<<< orphan*/  shader_data; TYPE_1__* shader; scalar_t__ have_sync; } ;
typedef  TYPE_2__ gl_t ;
struct TYPE_17__ {int /*<<< orphan*/  vao; } ;
typedef  TYPE_3__ gl2_renderchain_data_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_REFERENCE_BUFFER_SCE ; 
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  gl2_context_bind_hw_render (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gl2_deinit_chain (TYPE_2__*) ; 
 int /*<<< orphan*/  gl2_destroy_resources (TYPE_2__*) ; 
 int /*<<< orphan*/  gl2_free_overlay (TYPE_2__*) ; 
 int /*<<< orphan*/  gl2_renderchain_deinit_fbo (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gl2_renderchain_deinit_hw_render (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gl2_renderchain_fence_free (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gl2_video_layout_free (TYPE_2__*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDeleteTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  glDeleteVertexArrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scaler_ctx_gen_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_context_driver_free () ; 

__attribute__((used)) static void gl2_free(void *data)
{
   gl_t *gl = (gl_t*)data;
   if (!gl)
      return;

#ifdef HAVE_VIDEO_LAYOUT
   gl2_video_layout_free(gl);
#endif

   gl2_context_bind_hw_render(gl, false);

   if (gl->have_sync)
      gl2_renderchain_fence_free(gl,
            (gl2_renderchain_data_t*)
            gl->renderchain_data);

   font_driver_free_osd();

   gl->shader->deinit(gl->shader_data);

   glDeleteTextures(gl->textures, gl->texture);

#if defined(HAVE_MENU)
   if (gl->menu_texture)
      glDeleteTextures(1, &gl->menu_texture);
#endif

#ifdef HAVE_OVERLAY
   gl2_free_overlay(gl);
#endif

#if defined(HAVE_PSGL)
   glBindBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE, 0);
   glDeleteBuffers(1, &gl->pbo);
#endif

   scaler_ctx_gen_reset(&gl->scaler);

   if (gl->pbo_readback_enable)
   {
      glDeleteBuffers(4, gl->pbo_readback);
      scaler_ctx_gen_reset(&gl->pbo_readback_scaler);
   }

#ifndef HAVE_OPENGLES
   if (gl->core_context_in_use)
   {
      gl2_renderchain_data_t *chain = (gl2_renderchain_data_t*)
         gl->renderchain_data;

      glBindVertexArray(0);
      glDeleteVertexArrays(1, &chain->vao);
   }
#endif

   gl2_renderchain_deinit_fbo(gl, (gl2_renderchain_data_t*)gl->renderchain_data);
   gl2_renderchain_deinit_hw_render(gl, (gl2_renderchain_data_t*)gl->renderchain_data);
   gl2_deinit_chain(gl);

   video_context_driver_free();

   gl2_destroy_resources(gl);
}