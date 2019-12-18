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
struct gdbarch {char* (* construct_inferior_arguments ) (struct gdbarch*,int,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 char* stub1 (struct gdbarch*,int,char**) ; 

char *
gdbarch_construct_inferior_arguments (struct gdbarch *gdbarch, int argc, char **argv)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->construct_inferior_arguments != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_construct_inferior_arguments called\n");
  return gdbarch->construct_inferior_arguments (gdbarch, argc, argv);
}