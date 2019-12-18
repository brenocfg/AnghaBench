#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* main_func_highpc; void* main_func_lowpc; void* entry_func_highpc; void* entry_func_lowpc; void* deprecated_entry_file_highpc; void* deprecated_entry_file_lowpc; int /*<<< orphan*/  entry_point; } ;
struct objfile {TYPE_1__ ei; int /*<<< orphan*/  obfd; } ;

/* Variables and functions */
 int EXEC_P ; 
 void* INVALID_ENTRY_HIGHPC ; 
 void* INVALID_ENTRY_LOWPC ; 
 int /*<<< orphan*/  INVALID_ENTRY_POINT ; 
 int bfd_get_file_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_start_address (int /*<<< orphan*/ ) ; 

void
init_entry_point_info (struct objfile *objfile)
{
  /* Save startup file's range of PC addresses to help blockframe.c
     decide where the bottom of the stack is.  */

  if (bfd_get_file_flags (objfile->obfd) & EXEC_P)
    {
      /* Executable file -- record its entry point so we'll recognize
         the startup file because it contains the entry point.  */
      objfile->ei.entry_point = bfd_get_start_address (objfile->obfd);
    }
  else
    {
      /* Examination of non-executable.o files.  Short-circuit this stuff.  */
      objfile->ei.entry_point = INVALID_ENTRY_POINT;
    }
  objfile->ei.deprecated_entry_file_lowpc = INVALID_ENTRY_LOWPC;
  objfile->ei.deprecated_entry_file_highpc = INVALID_ENTRY_HIGHPC;
  objfile->ei.entry_func_lowpc = INVALID_ENTRY_LOWPC;
  objfile->ei.entry_func_highpc = INVALID_ENTRY_HIGHPC;
  objfile->ei.main_func_lowpc = INVALID_ENTRY_LOWPC;
  objfile->ei.main_func_highpc = INVALID_ENTRY_HIGHPC;
}