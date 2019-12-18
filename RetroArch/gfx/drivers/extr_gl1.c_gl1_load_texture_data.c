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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
typedef  enum gfx_wrap_type { ____Placeholder_gfx_wrap_type } gfx_wrap_type ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  RARCH_GL1_FORMAT32 ; 
 int /*<<< orphan*/  RARCH_GL1_INTERNAL_FORMAT32 ; 
 int /*<<< orphan*/  RARCH_GL1_TEXTURE_TYPE32 ; 
#define  TEXTURE_FILTER_LINEAR 131 
#define  TEXTURE_FILTER_MIPMAP_LINEAR 130 
#define  TEXTURE_FILTER_MIPMAP_NEAREST 129 
#define  TEXTURE_FILTER_NEAREST 128 
 int /*<<< orphan*/  gl1_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl1_wrap_type_to_enum (int) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int video_driver_supports_rgba () ; 

__attribute__((used)) static void gl1_load_texture_data(
      GLuint id,
      enum gfx_wrap_type wrap_type,
      enum texture_filter_type filter_type,
      unsigned alignment,
      unsigned width, unsigned height,
      const void *frame, unsigned base_size)
{
   GLint mag_filter, min_filter;
   bool use_rgba    = video_driver_supports_rgba();
   bool rgb32       = (base_size == (sizeof(uint32_t)));
   GLenum wrap      = gl1_wrap_type_to_enum(wrap_type);

   /* GL1.x does not have mipmapping support. */
   switch (filter_type)
   {
      case TEXTURE_FILTER_MIPMAP_NEAREST:
      case TEXTURE_FILTER_NEAREST:
         min_filter = GL_NEAREST;
         mag_filter = GL_NEAREST;
         break;
      case TEXTURE_FILTER_MIPMAP_LINEAR:
      case TEXTURE_FILTER_LINEAR:
      default:
         min_filter = GL_LINEAR;
         mag_filter = GL_LINEAR;
         break;
   }

   gl1_bind_texture(id, wrap, mag_filter, min_filter);

#ifndef VITA
   glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
#endif

   glTexImage2D(GL_TEXTURE_2D,
         0,
         (use_rgba || !rgb32) ? GL_RGBA : RARCH_GL1_INTERNAL_FORMAT32,
         width, height, 0,
         (use_rgba || !rgb32) ? GL_RGBA : RARCH_GL1_TEXTURE_TYPE32,
         (rgb32) ? RARCH_GL1_FORMAT32 : GL_UNSIGNED_BYTE, frame);
}