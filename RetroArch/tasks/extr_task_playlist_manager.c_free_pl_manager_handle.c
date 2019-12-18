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
struct TYPE_5__ {int /*<<< orphan*/ * playlist; struct TYPE_5__* playlist_name; struct TYPE_5__* playlist_path; } ;
typedef  TYPE_1__ pl_manager_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  playlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (TYPE_1__*) ; 

__attribute__((used)) static void free_pl_manager_handle(pl_manager_handle_t *pl_manager)
{
   if (!pl_manager)
      return;
   
   if (!string_is_empty(pl_manager->playlist_path))
   {
      free(pl_manager->playlist_path);
      pl_manager->playlist_path = NULL;
   }
   
   if (!string_is_empty(pl_manager->playlist_name))
   {
      free(pl_manager->playlist_name);
      pl_manager->playlist_name = NULL;
   }
   
   if (pl_manager->playlist)
   {
      playlist_free(pl_manager->playlist);
      pl_manager->playlist = NULL;
   }
   
   free(pl_manager);
   pl_manager = NULL;
}