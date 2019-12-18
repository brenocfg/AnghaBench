#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct texture_image {int dummy; } ;
struct overlay {size_t pos; unsigned int load_images_size; unsigned int size; scalar_t__ conf; struct overlay* overlays; struct texture_image* load_images; struct overlay* overlay_path; } ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
typedef  struct overlay overlay_loader_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_free (scalar_t__) ; 
 int /*<<< orphan*/  free (struct overlay*) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  input_overlay_free_overlay (struct overlay*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 

__attribute__((used)) static void task_overlay_free(retro_task_t *task)
{
   unsigned i;
   overlay_loader_t *loader  = (overlay_loader_t*)task->state;
   struct overlay *overlay   = &loader->overlays[loader->pos];

   if (loader->overlay_path)
      free(loader->overlay_path);

   if (task_get_cancelled(task))
   {
      for (i = 0; i < overlay->load_images_size; i++)
      {
         struct texture_image *ti = &overlay->load_images[i];
         image_texture_free(ti);
      }

      for (i = 0; i < loader->size; i++)
         input_overlay_free_overlay(&loader->overlays[i]);

      free(loader->overlays);
   }

   if (loader->conf)
      config_file_free(loader->conf);

   free(loader);
}