#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  coord; } ;
struct TYPE_5__ {unsigned int* last_width; size_t tex_index; unsigned int* last_height; int tex_w; int tex_h; int base_size; int textures; TYPE_1__ tex_info; scalar_t__ empty_buf; int /*<<< orphan*/  texture_fmt; int /*<<< orphan*/  texture_type; } ;
typedef  TYPE_2__ gl_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_REFERENCE_BUFFER_SCE ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  glBufferSubData (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexSubImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_texture_coords (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  video_pixel_get_alignment (unsigned int) ; 

__attribute__((used)) static void gl2_update_input_size(gl_t *gl, unsigned width,
      unsigned height, unsigned pitch, bool clear)
{
   float xamt, yamt;

   if ((width != gl->last_width[gl->tex_index] ||
            height != gl->last_height[gl->tex_index]) && gl->empty_buf)
   {
      /* Resolution change. Need to clear out texture. */

      gl->last_width[gl->tex_index]  = width;
      gl->last_height[gl->tex_index] = height;

      if (clear)
      {
         glPixelStorei(GL_UNPACK_ALIGNMENT,
               video_pixel_get_alignment(width * sizeof(uint32_t)));
#if defined(HAVE_PSGL)
         glBufferSubData(GL_TEXTURE_REFERENCE_BUFFER_SCE,
               gl->tex_w * gl->tex_h * gl->tex_index * gl->base_size,
               gl->tex_w * gl->tex_h * gl->base_size,
               gl->empty_buf);
#else
         glTexSubImage2D(GL_TEXTURE_2D,
               0, 0, 0, gl->tex_w, gl->tex_h, gl->texture_type,
               gl->texture_fmt, gl->empty_buf);
#endif
      }
   }
   /* We might have used different texture coordinates
    * last frame. Edge case if resolution changes very rapidly. */
   else if ((width !=
            gl->last_width[(gl->tex_index + gl->textures - 1) % gl->textures]) ||
         (height !=
          gl->last_height[(gl->tex_index + gl->textures - 1) % gl->textures])) { }
   else
      return;

   xamt = (float)width  / gl->tex_w;
   yamt = (float)height / gl->tex_h;
   set_texture_coords(gl->tex_info.coord, xamt, yamt);
}