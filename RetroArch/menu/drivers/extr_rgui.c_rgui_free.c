#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * thumbnail_path_data; } ;
typedef  TYPE_1__ rgui_t ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_thumbnail ; 
 int /*<<< orphan*/  mini_left_thumbnail ; 
 int /*<<< orphan*/  mini_thumbnail ; 
 int /*<<< orphan*/  rgui_background_free () ; 
 int /*<<< orphan*/  rgui_framebuffer_free () ; 
 int /*<<< orphan*/  rgui_thumbnail_free (int /*<<< orphan*/ *) ; 
 TYPE_2__ rgui_upscale_buf ; 

__attribute__((used)) static void rgui_free(void *data)
{
   rgui_t *rgui = (rgui_t*)data;

   if (rgui)
   {
      if (rgui->thumbnail_path_data)
         free(rgui->thumbnail_path_data);
   }

   rgui_framebuffer_free();
   rgui_background_free();
   rgui_thumbnail_free(&fs_thumbnail);
   rgui_thumbnail_free(&mini_thumbnail);
   rgui_thumbnail_free(&mini_left_thumbnail);

   if (rgui_upscale_buf.data)
   {
      free(rgui_upscale_buf.data);
      rgui_upscale_buf.data = NULL;
   }
}