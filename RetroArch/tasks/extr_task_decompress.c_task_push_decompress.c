#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct archive_extract_userdata {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * title; void* user_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; TYPE_3__* state; void* frontend_userdata; } ;
typedef  TYPE_2__ retro_task_t ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * target_file; int /*<<< orphan*/ * subdir; struct archive_extract_userdata* userdata; TYPE_1__ archive; int /*<<< orphan*/ * valid_ext; int /*<<< orphan*/ * target_dir; int /*<<< orphan*/ * source_file; } ;
typedef  TYPE_3__ decompress_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_TRANSFER_INIT ; 
 int /*<<< orphan*/  MSG_EXTRACTING ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,...) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 char* path_get_extension (char const*) ; 
 int /*<<< orphan*/  path_is_valid (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal_noncase (char const*,char*) ; 
 scalar_t__ task_check_decompress (char const*) ; 
 int /*<<< orphan*/  task_decompress_handler ; 
 int /*<<< orphan*/  task_decompress_handler_subdir ; 
 int /*<<< orphan*/  task_decompress_handler_target_file ; 
 int /*<<< orphan*/  task_queue_push (TYPE_2__*) ; 

bool task_push_decompress(
      const char *source_file,
      const char *target_dir,
      const char *target_file,
      const char *subdir,
      const char *valid_ext,
      retro_task_callback_t cb,
      void *user_data,
      void *frontend_userdata)
{
   char tmp[PATH_MAX_LENGTH];
   const char *ext            = NULL;
   decompress_state_t *s      = NULL;
   retro_task_t *t            = NULL;

   tmp[0] = '\0';

   if (string_is_empty(target_dir) || string_is_empty(source_file))
   {
      RARCH_WARN(
            "[decompress] Empty or null source file or"
            " target directory arguments.\n");
      return false;
   }

   ext = path_get_extension(source_file);

   /* ZIP or APK only */
   if (
         !path_is_valid(source_file) ||
         (
             !string_is_equal_noncase(ext, "zip")
          && !string_is_equal_noncase(ext, "apk")
#ifdef HAVE_7ZIP
          && !string_is_equal_noncase(ext, "7z")
#endif
         )
      )
   {
      RARCH_WARN(
            "[decompress] File '%s' does not exist"
            " or is not a compressed file.\n",
            source_file);
      return false;
   }

   if (!valid_ext || !valid_ext[0])
      valid_ext   = NULL;

   if (task_check_decompress(source_file))
   {
      RARCH_LOG(
            "[decompress] File '%s' already being decompressed.\n",
            source_file);
      return false;
   }

   RARCH_LOG("[decompress] File '%s.\n", source_file);

   s              = (decompress_state_t*)calloc(1, sizeof(*s));

   if (!s)
      return false;

   t                   = (retro_task_t*)calloc(1, sizeof(*t));

   if (!t)
   {
      free(s);
      return false;
   }

   s->source_file      = strdup(source_file);
   s->target_dir       = strdup(target_dir);

   s->valid_ext        = valid_ext ? strdup(valid_ext) : NULL;
   s->archive.type     = ARCHIVE_TRANSFER_INIT;
   s->userdata         = (struct archive_extract_userdata*)
      calloc(1, sizeof(*s->userdata));

   t->frontend_userdata= frontend_userdata;

   t->state            = s;
   t->handler          = task_decompress_handler;

   if (!string_is_empty(subdir))
   {
      s->subdir        = strdup(subdir);
      t->handler       = task_decompress_handler_subdir;
   }
   else if (!string_is_empty(target_file))
   {
      s->target_file   = strdup(target_file);
      t->handler       = task_decompress_handler_target_file;
   }

   t->callback         = cb;
   t->user_data        = user_data;

   snprintf(tmp, sizeof(tmp), "%s '%s'",
         msg_hash_to_str(MSG_EXTRACTING),
         path_basename(source_file));

   t->title            = strdup(tmp);

   task_queue_push(t);

   return true;
}