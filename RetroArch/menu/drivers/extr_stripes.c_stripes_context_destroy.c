#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * list; } ;
struct TYPE_6__ {int /*<<< orphan*/ * font2; int /*<<< orphan*/ * font; int /*<<< orphan*/  savestate_thumbnail; int /*<<< orphan*/  left_thumbnail; int /*<<< orphan*/  thumbnail; TYPE_1__ textures; } ;
typedef  TYPE_2__ stripes_handle_t ;

/* Variables and functions */
 unsigned int STRIPES_TEXTURE_LAST ; 
 int /*<<< orphan*/  menu_display_font_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stripes_context_bg_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  stripes_context_destroy_horizontal_list (TYPE_2__*) ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_context_destroy(void *data)
{
   unsigned i;
   stripes_handle_t *stripes   = (stripes_handle_t*)data;

   if (!stripes)
      return;

   for (i = 0; i < STRIPES_TEXTURE_LAST; i++)
      video_driver_texture_unload(&stripes->textures.list[i]);

   video_driver_texture_unload(&stripes->thumbnail);
   video_driver_texture_unload(&stripes->left_thumbnail);
   video_driver_texture_unload(&stripes->savestate_thumbnail);

   stripes_context_destroy_horizontal_list(stripes);
   stripes_context_bg_destroy(stripes);

   menu_display_font_free(stripes->font);
   menu_display_font_free(stripes->font2);

   stripes->font = NULL;
   stripes->font2 = NULL;
}