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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct ui_file* gdb_fopen (char*,char*) ; 
 struct ui_file* gdb_stdout ; 
 int /*<<< orphan*/  gdbarch_dump (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 

__attribute__((used)) static void
maintenance_print_architecture (char *args, int from_tty)
{
  if (args == NULL)
    gdbarch_dump (current_gdbarch, gdb_stdout);
  else
    {
      struct ui_file *file = gdb_fopen (args, "w");
      if (file == NULL)
	perror_with_name ("maintenance print architecture");
      gdbarch_dump (current_gdbarch, file);    
      ui_file_delete (file);
    }
}