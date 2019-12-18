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
 int /*<<< orphan*/  CMD_EVENT_UNLOAD_CORE ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 scalar_t__ filestream_delete (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  generic_action_ok_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_flush_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static int action_ok_core_delete(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   const char *path_core = path_get(RARCH_PATH_CORE);
   char *core_path       = !string_is_empty(path_core)
      ? strdup(path_core) : NULL;

   if (!core_path)
      return 0;

   generic_action_ok_command(CMD_EVENT_UNLOAD_CORE);
   menu_entries_flush_stack(0, 0);

   if (filestream_delete(core_path) != 0) { }

   free(core_path);

   return 0;
}