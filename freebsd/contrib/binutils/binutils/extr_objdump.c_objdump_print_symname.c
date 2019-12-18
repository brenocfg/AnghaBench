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
struct disassemble_info {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,char const*) ;} ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 char* bfd_demangle (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ do_demangle ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
objdump_print_symname (bfd *abfd, struct disassemble_info *info,
		       asymbol *sym)
{
  char *alloc;
  const char *name;

  alloc = NULL;
  name = bfd_asymbol_name (sym);
  if (do_demangle && name[0] != '\0')
    {
      /* Demangle the name.  */
      alloc = bfd_demangle (abfd, name, DMGL_ANSI | DMGL_PARAMS);
      if (alloc != NULL)
	name = alloc;
    }

  if (info != NULL)
    (*info->fprintf_func) (info->stream, "%s", name);
  else
    printf ("%s", name);

  if (alloc != NULL)
    free (alloc);
}