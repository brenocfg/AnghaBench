#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_9__ {int const* vertex; } ;
struct TYPE_10__ {size_t tex_index; TYPE_2__ coords; TYPE_1__* fbo_rect; int /*<<< orphan*/ * texture; } ;
typedef  TYPE_3__ gl_t ;
struct TYPE_11__ {scalar_t__ has_srgb_fbo; int /*<<< orphan*/ * fbo; } ;
typedef  TYPE_4__ gl2_renderchain_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  img_height; int /*<<< orphan*/  img_width; } ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAMEBUFFER_SRGB ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  gl2_bind_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl2_set_viewport (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl2_renderchain_start_render(
      gl_t *gl,
      gl2_renderchain_data_t *chain,
      video_frame_info_t *video_info)
{
   /* Used when rendering to an FBO.
    * Texture coords have to be aligned
    * with vertex coordinates. */
   static const GLfloat fbo_vertexes[] = {
      0, 0,
      1, 0,
      0, 1,
      1, 1
   };
   glBindTexture(GL_TEXTURE_2D, gl->texture[gl->tex_index]);
   gl2_bind_fb(chain->fbo[0]);

   gl2_set_viewport(gl,
         video_info, gl->fbo_rect[0].img_width,
         gl->fbo_rect[0].img_height, true, false);

   /* Need to preserve the "flipped" state when in FBO
    * as well to have consistent texture coordinates.
    *
    * We will "flip" it in place on last pass. */
   gl->coords.vertex = fbo_vertexes;

#if defined(GL_FRAMEBUFFER_SRGB) && !defined(HAVE_OPENGLES)
   if (chain->has_srgb_fbo)
      glEnable(GL_FRAMEBUFFER_SRGB);
#endif
}