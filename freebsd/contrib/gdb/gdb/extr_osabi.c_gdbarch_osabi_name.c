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
typedef  enum gdb_osabi { ____Placeholder_gdb_osabi } gdb_osabi ;

/* Variables and functions */
 int GDB_OSABI_INVALID ; 
 int GDB_OSABI_UNKNOWN ; 
 char const** gdb_osabi_names ; 

const char *
gdbarch_osabi_name (enum gdb_osabi osabi)
{
  if (osabi >= GDB_OSABI_UNKNOWN && osabi < GDB_OSABI_INVALID)
    return gdb_osabi_names[osabi];

  return gdb_osabi_names[GDB_OSABI_INVALID];
}