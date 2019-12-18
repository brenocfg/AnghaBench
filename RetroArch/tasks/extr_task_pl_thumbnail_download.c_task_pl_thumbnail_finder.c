#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ handler; scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  playlist_path; } ;
typedef  TYPE_2__ pl_thumb_handle_t ;

/* Variables and functions */
 int string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_pl_thumbnail_download_handler ; 

__attribute__((used)) static bool task_pl_thumbnail_finder(retro_task_t *task, void *user_data)
{
   pl_thumb_handle_t *pl_thumb = NULL;
   
   if (!task || !user_data)
      return false;
   
   if (task->handler != task_pl_thumbnail_download_handler)
      return false;
   
   pl_thumb = (pl_thumb_handle_t*)task->state;
   if (!pl_thumb)
      return false;
   
   return string_is_equal((const char*)user_data, pl_thumb->playlist_path);
}