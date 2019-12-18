#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct retro_hw_render_callback {int depth; int stencil; } ;
struct TYPE_6__ {unsigned int textures; int hw_render_fbo_init; int /*<<< orphan*/ * texture; int /*<<< orphan*/ * hw_render_fbo; int /*<<< orphan*/  has_fbo; } ;
typedef  TYPE_1__ gl_t ;
struct TYPE_7__ {int hw_render_depth_init; int /*<<< orphan*/ * hw_render_depth; } ;
typedef  TYPE_2__ gl2_renderchain_data_t ;
typedef  int /*<<< orphan*/  GLint ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_COMPONENT16 ; 
 int /*<<< orphan*/  GL_DEPTH_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_SIZE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  RARCH_ERR (char*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  RARCH_GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  RARCH_GL_DEPTH24_STENCIL8 ; 
 int /*<<< orphan*/  RARCH_GL_DEPTH_ATTACHMENT ; 
 int /*<<< orphan*/  RARCH_GL_FRAMEBUFFER ; 
 scalar_t__ RARCH_GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  RARCH_GL_MAX_RENDERBUFFER_SIZE ; 
 int /*<<< orphan*/  RARCH_GL_RENDERBUFFER ; 
 int /*<<< orphan*/  RARCH_GL_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  gl2_bind_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_bind_rb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gl2_check_fb_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_context_bind_hw_render (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gl2_fb_rb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_fb_texture_2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_gen_fb (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl2_gen_rb (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl2_rb_storage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gl2_renderchain_bind_backbuffer () ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct retro_hw_render_callback* video_driver_get_hw_context () ; 

__attribute__((used)) static bool gl2_renderchain_init_hw_render(
      gl_t *gl,
      gl2_renderchain_data_t *chain,
      unsigned width, unsigned height)
{
   GLenum status;
   unsigned i;
   bool depth                           = false;
   bool stencil                         = false;
   GLint max_fbo_size                   = 0;
   GLint max_renderbuffer_size          = 0;
   struct retro_hw_render_callback *hwr =
      video_driver_get_hw_context();

   /* We can only share texture objects through contexts.
    * FBOs are "abstract" objects and are not shared. */
   gl2_context_bind_hw_render(gl, true);

   RARCH_LOG("[GL]: Initializing HW render (%u x %u).\n", width, height);
   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_fbo_size);
   glGetIntegerv(RARCH_GL_MAX_RENDERBUFFER_SIZE, &max_renderbuffer_size);
   RARCH_LOG("[GL]: Max texture size: %d px, renderbuffer size: %d px.\n",
         max_fbo_size, max_renderbuffer_size);

   if (!gl->has_fbo)
      return false;

   RARCH_LOG("[GL]: Supports FBO (render-to-texture).\n");

   glBindTexture(GL_TEXTURE_2D, 0);
   gl2_gen_fb(gl->textures, gl->hw_render_fbo);

   depth   = hwr->depth;
   stencil = hwr->stencil;

   if (depth)
   {
      gl2_gen_rb(gl->textures, chain->hw_render_depth);
      chain->hw_render_depth_init = true;
   }

   for (i = 0; i < gl->textures; i++)
   {
      gl2_bind_fb(gl->hw_render_fbo[i]);
      gl2_fb_texture_2d(RARCH_GL_FRAMEBUFFER,
            RARCH_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl->texture[i], 0);

      if (depth)
      {
         gl2_bind_rb(RARCH_GL_RENDERBUFFER, chain->hw_render_depth[i]);
         gl2_rb_storage(RARCH_GL_RENDERBUFFER,
               stencil ? RARCH_GL_DEPTH24_STENCIL8 : GL_DEPTH_COMPONENT16,
               width, height);
         gl2_bind_rb(RARCH_GL_RENDERBUFFER, 0);

         if (stencil)
         {
#if defined(HAVE_OPENGLES2) || defined(HAVE_OPENGLES1) || ((defined(__MACH__) && (defined(__ppc__) || defined(__ppc64__))))
            /* GLES2 is a bit weird, as always.
             * There's no GL_DEPTH_STENCIL_ATTACHMENT like in desktop GL. */
            gl2_fb_rb(RARCH_GL_FRAMEBUFFER,
                  RARCH_GL_DEPTH_ATTACHMENT,
                  RARCH_GL_RENDERBUFFER,
                  chain->hw_render_depth[i]);
            gl2_fb_rb(RARCH_GL_FRAMEBUFFER,
                  RARCH_GL_STENCIL_ATTACHMENT,
                  RARCH_GL_RENDERBUFFER,
                  chain->hw_render_depth[i]);
#else
            /* We use ARB FBO extensions, no need to check. */
            gl2_fb_rb(RARCH_GL_FRAMEBUFFER,
                  GL_DEPTH_STENCIL_ATTACHMENT,
                  RARCH_GL_RENDERBUFFER,
                  chain->hw_render_depth[i]);
#endif
         }
         else
         {
            gl2_fb_rb(RARCH_GL_FRAMEBUFFER,
                  RARCH_GL_DEPTH_ATTACHMENT,
                  RARCH_GL_RENDERBUFFER,
                  chain->hw_render_depth[i]);
         }
      }

      status = gl2_check_fb_status(RARCH_GL_FRAMEBUFFER);
      if (status != RARCH_GL_FRAMEBUFFER_COMPLETE)
      {
         RARCH_ERR("[GL]: Failed to create HW render FBO #%u, error: 0x%04x.\n",
               i, status);
         return false;
      }
   }

   gl2_renderchain_bind_backbuffer();
   gl->hw_render_fbo_init = true;

   gl2_context_bind_hw_render(gl, false);
   return true;
}