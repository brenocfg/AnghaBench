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
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ retro_ctx_size_info_t ;
struct TYPE_5__ {void* data; scalar_t__ size; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_BYTES ; 
 int /*<<< orphan*/  MSG_FAILED_TO_SAVE_STATE_TO ; 
 int /*<<< orphan*/  MSG_FILE_ALREADY_EXISTS_SAVING_TO_BACKUP_BUFFER ; 
 int /*<<< orphan*/  MSG_SAVING_STATE ; 
 int /*<<< orphan*/  MSG_STATE_SIZE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  core_serialize_size (TYPE_1__*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* get_serialized_data (char const*,scalar_t__) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_valid (char const*) ; 
 int /*<<< orphan*/  save_state_in_background ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  task_push_load_and_save_state (char const*,void*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  task_push_save_state (char const*,void*,scalar_t__,int) ; 
 TYPE_2__ undo_load_buf ; 

bool content_save_state(const char *path, bool save_to_disk, bool autosave)
{
   retro_ctx_size_info_t info;
   void *data  = NULL;

   core_serialize_size(&info);

   if (info.size == 0)
      return false;

   if (!save_state_in_background)
   {
      RARCH_LOG("%s: \"%s\".\n",
            msg_hash_to_str(MSG_SAVING_STATE),
            path);

      data = get_serialized_data(path, info.size);

      if (!data)
      {
         RARCH_ERR("%s \"%s\".\n",
               msg_hash_to_str(MSG_FAILED_TO_SAVE_STATE_TO),
               path);
         return false;
      }

      RARCH_LOG("%s: %d %s.\n",
            msg_hash_to_str(MSG_STATE_SIZE),
            (int)info.size,
            msg_hash_to_str(MSG_BYTES));
   }

   if (save_to_disk)
   {
      if (path_is_valid(path) && !autosave)
      {
         /* Before overwritting the savestate file, load it into a buffer
         to allow undo_save_state() to work */
         /* TODO/FIXME - Use msg_hash_to_str here */
         RARCH_LOG("%s ...\n",
               msg_hash_to_str(MSG_FILE_ALREADY_EXISTS_SAVING_TO_BACKUP_BUFFER));

         task_push_load_and_save_state(path, data, info.size, true, autosave);
      }
      else
         task_push_save_state(path, data, info.size, autosave);
   }
   else
   {
      if (!data)
         data = get_serialized_data(path, info.size);

      if (!data)
      {
         RARCH_ERR("%s \"%s\".\n",
               msg_hash_to_str(MSG_FAILED_TO_SAVE_STATE_TO),
               path);
         return false;
      }
      /* save_to_disk is false, which means we are saving the state
      in undo_load_buf to allow content_undo_load_state() to restore it */

      /* If we were holding onto an old state already, clean it up first */
      if (undo_load_buf.data)
      {
         free(undo_load_buf.data);
         undo_load_buf.data = NULL;
      }

      undo_load_buf.data = malloc(info.size);
      if (!undo_load_buf.data)
      {
         free(data);
         return false;
      }

      memcpy(undo_load_buf.data, data, info.size);
      free(data);
      undo_load_buf.size = info.size;
      strlcpy(undo_load_buf.path, path, sizeof(undo_load_buf.path));
   }

   return true;
}