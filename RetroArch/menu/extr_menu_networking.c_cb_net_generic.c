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
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_3__ {char* core_buf; size_t core_len; } ;
typedef  TYPE_1__ menu_handle_t ;
typedef  char http_transfer_data_t ;
typedef  char file_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_INDEX_DIRS_URL ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_UNSET_REFRESH ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  cb_net_generic_subdir ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_parent_dir (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  net_http_urlencode_full (char*,char*,int) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_http_transfer (char*,int,char*,int /*<<< orphan*/ ,char*) ; 

void cb_net_generic(retro_task_t *task,
      void *task_data, void *user_data, const char *err)
{
#ifdef HAVE_NETWORKING
   bool refresh                   = false;
   http_transfer_data_t *data     = (http_transfer_data_t*)task_data;
   file_transfer_t *state         = (file_transfer_t*)user_data;
   menu_handle_t            *menu = menu_driver_get_ptr();

   if (!menu)
      goto finish;

   if (menu->core_buf)
      free(menu->core_buf);

   menu->core_buf = NULL;
   menu->core_len = 0;

   if (!data || err)
      goto finish;

   menu->core_buf = (char*)malloc((data->len+1) * sizeof(char));

   if (!menu->core_buf)
      goto finish;

   if (!string_is_empty(data->data))
      memcpy(menu->core_buf, data->data, data->len * sizeof(char));
   menu->core_buf[data->len] = '\0';
   menu->core_len            = data->len;

finish:
   refresh = true;
   menu_entries_ctl(MENU_ENTRIES_CTL_UNSET_REFRESH, &refresh);

   if (data)
   {
      if (data->data)
         free(data->data);
      free(data);
   }

   if (!err && !strstr(state->path, file_path_str(FILE_PATH_INDEX_DIRS_URL)))
   {
      char *parent_dir                 = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      char *parent_dir_encoded         = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
      file_transfer_t *transf     = NULL;

      parent_dir[0]         = '\0';
      parent_dir_encoded[0] = '\0';

      fill_pathname_parent_dir(parent_dir,
            state->path, PATH_MAX_LENGTH * sizeof(char));
      strlcat(parent_dir,
            file_path_str(FILE_PATH_INDEX_DIRS_URL),
            PATH_MAX_LENGTH * sizeof(char));

      transf           = (file_transfer_t*)malloc(sizeof(*transf));

      transf->enum_idx = MSG_UNKNOWN;
      strlcpy(transf->path, parent_dir, sizeof(transf->path));

      net_http_urlencode_full(parent_dir_encoded, parent_dir, PATH_MAX_LENGTH * sizeof(char));
      task_push_http_transfer(parent_dir_encoded, true,
            "index_dirs", cb_net_generic_subdir, transf);

      free(parent_dir);
      free(parent_dir_encoded);
   }

   if (state)
      free(state);
#endif
}