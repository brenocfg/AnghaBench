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
struct pr_handle {void* demangler; int /*<<< orphan*/ ** syms; int /*<<< orphan*/ * abfd; int /*<<< orphan*/ * filename; scalar_t__ parameter; int /*<<< orphan*/ * stack; scalar_t__ indent; int /*<<< orphan*/ * f; } ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ debug_write (void*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_fns ; 
 int /*<<< orphan*/  tg_fns ; 

bfd_boolean
print_debugging_info (FILE *f, void *dhandle, bfd *abfd, asymbol **syms,
		      void *demangler, bfd_boolean as_tags)
{
  struct pr_handle info;

  info.f = f;
  info.indent = 0;
  info.stack = NULL;
  info.parameter = 0;
  info.filename = NULL;
  info.abfd = abfd;
  info.syms = syms;
  info.demangler = demangler;

  if (as_tags)
    {
      fputs ("!_TAG_FILE_FORMAT\t2\t/extended format/\n", f);
      fputs ("!_TAG_FILE_SORTED\t0\t/0=unsorted, 1=sorted/\n", f);
      fputs ("!_TAG_PROGRAM_AUTHOR\tIan Lance Taylor, Salvador E. Tropea and others\t//\n", f);
      fputs ("!_TAG_PROGRAM_NAME\tobjdump\t/From GNU binutils/\n", f);
    }

  return as_tags ? debug_write (dhandle, &tg_fns, (void *) & info)
    : debug_write (dhandle, &pr_fns, (void *) & info);
}