#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ menu_linear_filter; } ;
struct TYPE_7__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_8__ {float menu_texture_alpha; scalar_t__ menu_texture; } ;
typedef  TYPE_3__ gl_core_t ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BLUE ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  GL_RED ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_RGBA4 ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_B ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_R ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNPACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT_4_4_4_4 ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glDeleteTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  glGenTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexStorage2D (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  glTexSubImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  gl_core_context_bind_hw_render (TYPE_3__*,int) ; 

__attribute__((used)) static void gl_core_set_texture_frame(void *data,
      const void *frame, bool rgb32, unsigned width, unsigned height,
      float alpha)
{
   GLenum menu_filter;
   settings_t *settings = config_get_ptr();
   unsigned base_size   = rgb32 ? sizeof(uint32_t) : sizeof(uint16_t);
   gl_core_t *gl        = (gl_core_t*)data;
   if (!gl)
      return;

   gl_core_context_bind_hw_render(gl, false);
   menu_filter = settings->bools.menu_linear_filter ? GL_LINEAR : GL_NEAREST;

   if (gl->menu_texture)
      glDeleteTextures(1, &gl->menu_texture);
   glGenTextures(1, &gl->menu_texture);
   glBindTexture(GL_TEXTURE_2D, gl->menu_texture);
   glTexStorage2D(GL_TEXTURE_2D, 1, rgb32 ? GL_RGBA8 : GL_RGBA4, width, height);

   glPixelStorei(GL_UNPACK_ALIGNMENT, base_size);
   glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
   glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                   width, height, GL_RGBA, rgb32 ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT_4_4_4_4, frame);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, menu_filter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, menu_filter);

   if (rgb32)
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
   }

   glBindTexture(GL_TEXTURE_2D, 0);
   gl->menu_texture_alpha = alpha;
   gl_core_context_bind_hw_render(gl, true);
}