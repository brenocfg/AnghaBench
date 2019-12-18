#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  texture_optimal; TYPE_2__* vk; int /*<<< orphan*/  texture; scalar_t__ font_data; TYPE_3__* font_driver; } ;
typedef  TYPE_4__ vulkan_raster_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* free ) (scalar_t__) ;} ;
struct TYPE_7__ {TYPE_1__* context; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  vkQueueWaitIdle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_destroy_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_raster_font_free_font(void *data, bool is_threaded)
{
   vulkan_raster_t *font = (vulkan_raster_t*)data;
   if (!font)
      return;

   if (font->font_driver && font->font_data)
      font->font_driver->free(font->font_data);

   vkQueueWaitIdle(font->vk->context->queue);
   vulkan_destroy_texture(
         font->vk->context->device, &font->texture);
   vulkan_destroy_texture(
         font->vk->context->device, &font->texture_optimal);

   free(font);
}