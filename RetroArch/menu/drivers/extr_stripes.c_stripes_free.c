#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  carr; } ;
struct TYPE_4__ {int /*<<< orphan*/  carr; } ;
struct TYPE_6__ {int /*<<< orphan*/  bg_file_path; int /*<<< orphan*/  left_thumbnail_file_path; int /*<<< orphan*/  thumbnail_file_path; int /*<<< orphan*/  savestate_thumbnail_file_path; int /*<<< orphan*/  thumbnail_content; int /*<<< orphan*/  thumbnail_system; int /*<<< orphan*/  box_message; TYPE_2__ raster_block2; TYPE_1__ raster_block; int /*<<< orphan*/ * horizontal_list; int /*<<< orphan*/ * selection_buf_old; } ;
typedef  TYPE_3__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  font_driver_bind_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_free_list_nodes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  video_coord_array_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_free(void *data)
{
   stripes_handle_t *stripes = (stripes_handle_t*)data;

   if (stripes)
   {
      if (stripes->selection_buf_old)
      {
         stripes_free_list_nodes(stripes->selection_buf_old, false);
         file_list_free(stripes->selection_buf_old);
      }

      if (stripes->horizontal_list)
      {
         stripes_free_list_nodes(stripes->horizontal_list, false);
         file_list_free(stripes->horizontal_list);
      }

      stripes->selection_buf_old = NULL;
      stripes->horizontal_list   = NULL;

      video_coord_array_free(&stripes->raster_block.carr);
      video_coord_array_free(&stripes->raster_block2.carr);

      if (!string_is_empty(stripes->box_message))
         free(stripes->box_message);
      if (!string_is_empty(stripes->thumbnail_system))
         free(stripes->thumbnail_system);
      if (!string_is_empty(stripes->thumbnail_content))
         free(stripes->thumbnail_content);
      if (!string_is_empty(stripes->savestate_thumbnail_file_path))
         free(stripes->savestate_thumbnail_file_path);
      if (!string_is_empty(stripes->thumbnail_file_path))
         free(stripes->thumbnail_file_path);
      if (!string_is_empty(stripes->left_thumbnail_file_path))
         free(stripes->left_thumbnail_file_path);
      if (!string_is_empty(stripes->bg_file_path))
         free(stripes->bg_file_path);
   }

   font_driver_bind_block(NULL, NULL);
}