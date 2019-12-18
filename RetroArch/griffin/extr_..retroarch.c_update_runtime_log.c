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
typedef  int /*<<< orphan*/  runtime_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libretro_core_runtime_usec ; 
 int /*<<< orphan*/  runtime_content_path ; 
 int /*<<< orphan*/  runtime_core_path ; 
 int /*<<< orphan*/  runtime_log_add_runtime_usec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * runtime_log_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  runtime_log_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runtime_log_set_last_played_now (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_runtime_log(bool log_per_core)
{
   /* Initialise runtime log file */
   runtime_log_t *runtime_log = runtime_log_init(
         runtime_content_path, runtime_core_path, log_per_core);

   if (!runtime_log)
      return;

   /* Add additional runtime */
   runtime_log_add_runtime_usec(runtime_log, libretro_core_runtime_usec);

   /* Update 'last played' entry */
   runtime_log_set_last_played_now(runtime_log);

   /* Save runtime log file */
   runtime_log_save(runtime_log);

   /* Clean up */
   free(runtime_log);
}