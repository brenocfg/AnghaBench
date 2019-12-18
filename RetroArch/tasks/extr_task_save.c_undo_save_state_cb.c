#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  save_task_state_t ;
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_2__ {char* path; int /*<<< orphan*/ * data; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ undo_save_buf ; 

__attribute__((used)) static void undo_save_state_cb(retro_task_t *task,
      void *task_data,
      void *user_data, const char *error)
{
   save_task_state_t *state = (save_task_state_t*)task_data;

   /* Wipe the save file buffer as it's intended to be one use only */
   undo_save_buf.path[0] = '\0';
   undo_save_buf.size    = 0;
   if (undo_save_buf.data)
   {
      free(undo_save_buf.data);
      undo_save_buf.data = NULL;
   }

   free(state);
}