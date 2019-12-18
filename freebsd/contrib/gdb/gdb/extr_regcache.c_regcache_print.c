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
typedef  enum regcache_dump_what { ____Placeholder_regcache_dump_what } regcache_dump_what ;

/* Variables and functions */
 int /*<<< orphan*/  current_regcache ; 
 struct ui_file* gdb_fopen (char*,char*) ; 
 struct ui_file* gdb_stdout ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  regcache_dump (int /*<<< orphan*/ ,struct ui_file*,int) ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 

__attribute__((used)) static void
regcache_print (char *args, enum regcache_dump_what what_to_dump)
{
  if (args == NULL)
    regcache_dump (current_regcache, gdb_stdout, what_to_dump);
  else
    {
      struct ui_file *file = gdb_fopen (args, "w");
      if (file == NULL)
	perror_with_name ("maintenance print architecture");
      regcache_dump (current_regcache, file, what_to_dump);    
      ui_file_delete (file);
    }
}