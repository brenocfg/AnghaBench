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
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  int /*<<< orphan*/  parent_dir ;
typedef  void http_transfer_data_t ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ file_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_INDEX_DIRS_URL ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_parent_dir (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 
 int /*<<< orphan*/  string_is_empty (void*) ; 
 int /*<<< orphan*/  strstr (char*,int /*<<< orphan*/ ) ; 

void cb_net_generic_subdir(retro_task_t *task,
      void *task_data, void *user_data, const char *err)
{
#ifdef HAVE_NETWORKING
   char subdir_path[PATH_MAX_LENGTH];
   http_transfer_data_t *data        = (http_transfer_data_t*)task_data;
   file_transfer_t *state       = (file_transfer_t*)user_data;

   subdir_path[0] = '\0';

   if (!data || err)
      goto finish;

   if (!string_is_empty(data->data))
      memcpy(subdir_path, data->data, data->len * sizeof(char));
   subdir_path[data->len] = '\0';

finish:
   if (!err && !strstr(subdir_path, file_path_str(FILE_PATH_INDEX_DIRS_URL)))
   {
      char parent_dir[PATH_MAX_LENGTH];

      parent_dir[0] = '\0';

      fill_pathname_parent_dir(parent_dir,
            state->path, sizeof(parent_dir));

      /*generic_action_ok_displaylist_push(parent_dir, NULL,
            subdir_path, 0, 0, 0, ACTION_OK_DL_CORE_CONTENT_DIRS_SUBDIR_LIST);*/
   }

   if (data)
   {
      if (data->data)
         free(data->data);
      free(data);
   }

   if (user_data)
      free(user_data);
#endif
}