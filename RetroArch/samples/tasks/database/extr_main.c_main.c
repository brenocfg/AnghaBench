#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  core_info_deinit_list () ; 
 int /*<<< orphan*/  core_info_init_list (char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ loop_active ; 
 int /*<<< orphan*/  main_db_cb ; 
 int /*<<< orphan*/  main_msg_queue_push ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  task_push_dbscan (char const*,char const*,char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_queue_check () ; 
 int /*<<< orphan*/  task_queue_deinit () ; 
 int /*<<< orphan*/  task_queue_init (int,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
   const char *db_dir        = NULL;
   const char *core_info_dir = NULL;
   const char *core_dir      = NULL;
   const char *input_dir     = NULL;
   const char *playlist_dir  = NULL;
#if defined(_WIN32)
   const char *exts          = "dll";
#elif defined(__MACH__)
   const char *exts          = "dylib";
#else
   const char *exts          = "so";
#endif

   if (argc < 6)
   {
      fprintf(stderr, "Usage: %s <database dir> <core dir> <core info dir> <input dir> <playlist dir>\n", argv[0]);
      return 1;
   }

   db_dir        = argv[1];
   core_dir      = argv[2];
   core_info_dir = argv[3];
   input_dir     = argv[4];
   playlist_dir  = argv[5];

   fprintf(stderr, "RDB database dir: %s\n", db_dir);
   fprintf(stderr, "Core         dir: %s\n", core_dir);
   fprintf(stderr, "Core info    dir: %s\n", core_info_dir);
   fprintf(stderr, "Input        dir: %s\n", input_dir);
   fprintf(stderr, "Playlist     dir: %s\n", playlist_dir);
#ifdef HAVE_THREADS
   task_queue_init(true /* threaded enable */, main_msg_queue_push);
#else
   task_queue_init(false /* threaded enable */, main_msg_queue_push);
#endif
   core_info_init_list(core_info_dir, core_dir, exts, true);

   task_push_dbscan(playlist_dir, db_dir, input_dir, true,
         true, main_db_cb);

   while (loop_active)
      task_queue_check();

   fprintf(stderr, "Exit loop\n");

   core_info_deinit_list();
   task_queue_deinit();

   return 0;
}