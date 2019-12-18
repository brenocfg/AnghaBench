#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* thumbnail_path_data; int /*<<< orphan*/ * playlist; struct TYPE_5__* dir_thumbnails; struct TYPE_5__* playlist_path; struct TYPE_5__* system; } ;
typedef  TYPE_1__ pl_thumb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  playlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (TYPE_1__*) ; 

__attribute__((used)) static void free_pl_thumb_handle(pl_thumb_handle_t *pl_thumb, bool free_playlist)
{
   if (!pl_thumb)
      return;

   if (!string_is_empty(pl_thumb->system))
   {
      free(pl_thumb->system);
      pl_thumb->system = NULL;
   }

   if (!string_is_empty(pl_thumb->playlist_path))
   {
      free(pl_thumb->playlist_path);
      pl_thumb->playlist_path = NULL;
   }

   if (!string_is_empty(pl_thumb->dir_thumbnails))
   {
      free(pl_thumb->dir_thumbnails);
      pl_thumb->dir_thumbnails = NULL;
   }

   if (pl_thumb->playlist && free_playlist)
   {
      playlist_free(pl_thumb->playlist);
      pl_thumb->playlist = NULL;
   }

   if (pl_thumb->thumbnail_path_data)
   {
      free(pl_thumb->thumbnail_path_data);
      pl_thumb->thumbnail_path_data = NULL;
   }

   free(pl_thumb);
   pl_thumb = NULL;
}