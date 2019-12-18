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
typedef  int /*<<< orphan*/  video_info_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int tex_w; int tex_h; int base_size; int textures; size_t tex_index; int /*<<< orphan*/ * texture; scalar_t__ renderchain_data; int /*<<< orphan*/  tex_min_filter; int /*<<< orphan*/  tex_mag_filter; int /*<<< orphan*/  wrap_mode; scalar_t__ hw_render_use; int /*<<< orphan*/  pbo; int /*<<< orphan*/  texture_fmt; int /*<<< orphan*/  texture_type; int /*<<< orphan*/  internal_fmt; } ;
typedef  TYPE_1__ gl_t ;
typedef  int /*<<< orphan*/  gl2_renderchain_data_t ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CAPS_ARGB8 ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_REFERENCE_BUFFER_SCE ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT_5_6_5 ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  gl2_renderchain_init_texture_reference (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gl_check_capability (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl2_init_textures(gl_t *gl, const video_info_t *video)
{
   unsigned i;
   GLenum internal_fmt = gl->internal_fmt;
   GLenum texture_type = gl->texture_type;
   GLenum texture_fmt  = gl->texture_fmt;

#ifdef HAVE_PSGL
   if (!gl->pbo)
      glGenBuffers(1, &gl->pbo);

   glBindBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE, gl->pbo);
   glBufferData(GL_TEXTURE_REFERENCE_BUFFER_SCE,
         gl->tex_w * gl->tex_h * gl->base_size * gl->textures,
         NULL, GL_STREAM_DRAW);
#endif

#if defined(HAVE_OPENGLES) && !defined(HAVE_PSGL)
   /* GLES is picky about which format we use here.
    * Without extensions, we can *only* render to 16-bit FBOs. */

   if (gl->hw_render_use && gl->base_size == sizeof(uint32_t))
   {
      if (gl_check_capability(GL_CAPS_ARGB8))
      {
         internal_fmt = GL_RGBA;
         texture_type = GL_RGBA;
         texture_fmt  = GL_UNSIGNED_BYTE;
      }
      else
      {
         RARCH_WARN("[GL]: 32-bit FBO not supported. Falling back to 16-bit.\n");
         internal_fmt = GL_RGB;
         texture_type = GL_RGB;
         texture_fmt  = GL_UNSIGNED_SHORT_5_6_5;
      }
   }
#endif

   glGenTextures(gl->textures, gl->texture);

   for (i = 0; i < gl->textures; i++)
   {
      gl_bind_texture(gl->texture[i], gl->wrap_mode, gl->tex_mag_filter,
            gl->tex_min_filter);

      gl2_renderchain_init_texture_reference(
            gl, (gl2_renderchain_data_t*)gl->renderchain_data,
            i, internal_fmt,
            texture_fmt, texture_type);
   }

   glBindTexture(GL_TEXTURE_2D, gl->texture[gl->tex_index]);
}