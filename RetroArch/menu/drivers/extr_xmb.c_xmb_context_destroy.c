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
typedef  TYPE_2__ xmb_handle_t ;

/* Variables and functions */
 unsigned int XMB_TEXTURE_LAST ; 
 int /*<<< orphan*/  menu_display_font_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmb_context_bg_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  xmb_context_destroy_horizontal_list (TYPE_2__*) ; 

__attribute__((used)) static void xmb_context_destroy(void *data)
{
   unsigned i;
   xmb_handle_t *xmb   = (xmb_handle_t*)data;

   if (!xmb)
      return;

   for (i = 0; i < XMB_TEXTURE_LAST; i++)
      video_driver_texture_unload(&xmb->textures.list[i]);

   video_driver_texture_unload(&xmb->thumbnail);
   video_driver_texture_unload(&xmb->left_thumbnail);
   video_driver_texture_unload(&xmb->savestate_thumbnail);

   xmb_context_destroy_horizontal_list(xmb);
   xmb_context_bg_destroy(xmb);

   menu_display_font_free(xmb->font);
   menu_display_font_free(xmb->font2);

   xmb->font = NULL;
   xmb->font2 = NULL;
}