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
typedef  int /*<<< orphan*/  uint8_t ;
struct retro_hw_render_callback {scalar_t__ context_type; int version_major; } ;
struct TYPE_7__ {size_t tex_width; int /*<<< orphan*/  tex_height; TYPE_2__* atlas; TYPE_1__* gl; } ;
typedef  TYPE_3__ gl_raster_t ;
struct TYPE_6__ {unsigned int height; unsigned int width; int /*<<< orphan*/ * buffer; } ;
struct TYPE_5__ {scalar_t__ core_context_in_use; } ;
typedef  void* GLint ;
typedef  void* GLenum ;

/* Variables and functions */
 void* GL_LUMINANCE_ALPHA ; 
 void* GL_ONE ; 
 void* GL_R8 ; 
 void* GL_RED ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_RGBA ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__ RETRO_HW_CONTEXT_OPENGL ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexParameteriv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct retro_hw_render_callback* video_driver_get_hw_context () ; 

__attribute__((used)) static bool gl_raster_font_upload_atlas(gl_raster_t *font)
{
   unsigned i, j;
   GLint  gl_internal                   = GL_LUMINANCE_ALPHA;
   GLenum gl_format                     = GL_LUMINANCE_ALPHA;
   size_t ncomponents                   = 2;
   uint8_t       *tmp                   = NULL;
#if defined(GL_VERSION_3_0)
   struct retro_hw_render_callback *hwr = video_driver_get_hw_context();

    if (font->gl->core_context_in_use ||
        (hwr->context_type == RETRO_HW_CONTEXT_OPENGL &&
         hwr->version_major >= 3))
   {
      GLint swizzle[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
      glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);

      gl_internal = GL_R8;
      gl_format   = GL_RED;
      ncomponents = 1;
   }
#endif

   tmp = (uint8_t*)calloc(font->tex_height, font->tex_width * ncomponents);

   switch (ncomponents)
   {
      case 1:
         for (i = 0; i < font->atlas->height; ++i)
         {
            const uint8_t *src = &font->atlas->buffer[i * font->atlas->width];
            uint8_t       *dst = &tmp[i * font->tex_width * ncomponents];

            memcpy(dst, src, font->atlas->width);
         }
         break;
      case 2:
         for (i = 0; i < font->atlas->height; ++i)
         {
            const uint8_t *src = &font->atlas->buffer[i * font->atlas->width];
            uint8_t       *dst = &tmp[i * font->tex_width * ncomponents];

            for (j = 0; j < font->atlas->width; ++j)
            {
               *dst++ = 0xff;
               *dst++ = *src++;
            }
         }
         break;
   }

   glTexImage2D(GL_TEXTURE_2D, 0, gl_internal, font->tex_width, font->tex_height,
         0, gl_format, GL_UNSIGNED_BYTE, tmp);

   free(tmp);

   return true;
}