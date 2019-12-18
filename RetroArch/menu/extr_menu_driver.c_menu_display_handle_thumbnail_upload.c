#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void texture_image ;
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; void* data; } ;
typedef  TYPE_1__ menu_ctx_load_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_IMAGE_THUMBNAIL ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  image_texture_free (void*) ; 
 int /*<<< orphan*/  menu_driver_load_image (TYPE_1__*) ; 

void menu_display_handle_thumbnail_upload(retro_task_t *task,
      void *task_data,
      void *user_data, const char *err)
{
   menu_ctx_load_image_t load_image_info;
   struct texture_image *img = (struct texture_image*)task_data;

   load_image_info.data = img;
   load_image_info.type = MENU_IMAGE_THUMBNAIL;

   menu_driver_load_image(&load_image_info);

   image_texture_free(img);
   free(img);
   free(user_data);
}