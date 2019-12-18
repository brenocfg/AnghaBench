#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * extensions; scalar_t__ menu_tex; scalar_t__ tex; } ;
typedef  TYPE_1__ gl1_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gl1_context_bind_hw_render (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gl1_free_overlay (TYPE_1__*) ; 
 TYPE_1__* gl1_menu_frame ; 
 TYPE_1__* gl1_menu_video_buf ; 
 TYPE_1__* gl1_video_buf ; 
 int /*<<< orphan*/  glDeleteTextures (int,scalar_t__*) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_context_driver_free () ; 

__attribute__((used)) static void gl1_gfx_free(void *data)
{
   gl1_t *gl1 = (gl1_t*)data;

   gl1_context_bind_hw_render(gl1, false);

   if (gl1_menu_frame)
   {
      free(gl1_menu_frame);
      gl1_menu_frame = NULL;
   }

   if (gl1_video_buf)
   {
      free(gl1_video_buf);
      gl1_video_buf = NULL;
   }

   if (gl1_menu_video_buf)
   {
      free(gl1_menu_video_buf);
      gl1_menu_video_buf = NULL;
   }

   if (!gl1)
      return;

   if (gl1->tex)
   {
      glDeleteTextures(1, &gl1->tex);
      gl1->tex = 0;
   }

   if (gl1->menu_tex)
   {
      glDeleteTextures(1, &gl1->menu_tex);
      gl1->menu_tex = 0;
   }

#ifdef HAVE_OVERLAY
   gl1_free_overlay(gl1);
#endif

   if (gl1->extensions)
   {
      string_list_free(gl1->extensions);
      gl1->extensions = NULL;
   }

   font_driver_free_osd();
   video_context_driver_free();
   free(gl1);
}