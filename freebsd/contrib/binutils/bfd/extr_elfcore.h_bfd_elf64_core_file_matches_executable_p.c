#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {scalar_t__ xvec; char const* filename; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_7__ {char* core_program; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_2__* elf_tdata (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

bfd_boolean
elf_core_file_matches_executable_p (bfd *core_bfd, bfd *exec_bfd)
{
  char* corename;

  /* xvecs must match if both are ELF files for the same target.  */

  if (core_bfd->xvec != exec_bfd->xvec)
    {
      bfd_set_error (bfd_error_system_call);
      return FALSE;
    }

  /* See if the name in the corefile matches the executable name.  */
  corename = elf_tdata (core_bfd)->core_program;
  if (corename != NULL)
    {
      const char* execname = strrchr (exec_bfd->filename, '/');

      execname = execname ? execname + 1 : exec_bfd->filename;

      if (strcmp (execname, corename) != 0)
	return FALSE;
    }

  return TRUE;
}