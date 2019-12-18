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
struct TYPE_8__ {float menu_texture_alpha; size_t tex_index; int /*<<< orphan*/ * texture; int /*<<< orphan*/  menu_texture; } ;
typedef  TYPE_3__ gl_t ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  RARCH_WRAP_EDGE ; 
 int TEXTURE_FILTER_LINEAR ; 
 int TEXTURE_FILTER_NEAREST ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  gl2_context_bind_hw_render (TYPE_3__*,int) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_load_texture_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,unsigned int,void const*,unsigned int) ; 
 int /*<<< orphan*/  video_pixel_get_alignment (unsigned int) ; 

__attribute__((used)) static void gl2_set_texture_frame(void *data,
      const void *frame, bool rgb32, unsigned width, unsigned height,
      float alpha)
{
   enum texture_filter_type menu_filter;
   settings_t *settings            = config_get_ptr();
   unsigned base_size              = rgb32 ? sizeof(uint32_t) : sizeof(uint16_t);
   gl_t *gl                        = (gl_t*)data;
   if (!gl)
      return;

   gl2_context_bind_hw_render(gl, false);

   menu_filter = settings->bools.menu_linear_filter ? TEXTURE_FILTER_LINEAR : TEXTURE_FILTER_NEAREST;

   if (!gl->menu_texture)
      glGenTextures(1, &gl->menu_texture);

   gl_load_texture_data(gl->menu_texture,
         RARCH_WRAP_EDGE, menu_filter,
         video_pixel_get_alignment(width * base_size),
         width, height, frame,
         base_size);

   gl->menu_texture_alpha = alpha;
   glBindTexture(GL_TEXTURE_2D, gl->texture[gl->tex_index]);

   gl2_context_bind_hw_render(gl, true);
}