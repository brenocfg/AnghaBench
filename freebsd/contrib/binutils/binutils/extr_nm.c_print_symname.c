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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 char* bfd_demangle (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ do_demangle ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char const*,char const*) ; 

__attribute__((used)) static void
print_symname (const char *format, const char *name, bfd *abfd)
{
  if (do_demangle && *name)
    {
      char *res = bfd_demangle (abfd, name, DMGL_ANSI | DMGL_PARAMS);

      if (res != NULL)
	{
	  printf (format, res);
	  free (res);
	  return;
	}
    }

  printf (format, name);
}