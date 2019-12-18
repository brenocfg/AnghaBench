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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_com_alias (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  exec_set_find_memory_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcore_command ; 
 int /*<<< orphan*/  objfile_find_memory_regions ; 

void
_initialize_gcore (void)
{
  add_com ("generate-core-file", class_files, gcore_command,
	   "\
Save a core file with the current state of the debugged process.\n\
Argument is optional filename.  Default filename is 'core.<process_id>'.");

  add_com_alias ("gcore", "generate-core-file", class_files, 1);
  exec_set_find_memory_regions (objfile_find_memory_regions);
}