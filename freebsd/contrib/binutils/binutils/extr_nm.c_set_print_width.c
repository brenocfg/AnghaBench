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
 int bfd_get_arch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_target (int /*<<< orphan*/ *) ; 
 int print_width ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
set_print_width (bfd *file)
{
  print_width = bfd_get_arch_size (file);

  if (print_width == -1)
    {
      /* PR binutils/4292
	 Guess the target's bitsize based on its name.
	 We assume here than any 64-bit format will include
	 "64" somewhere in its name.  The only known exception
	 is the MMO object file format.  */
      if (strstr (bfd_get_target (file), "64") != NULL
	  || strcmp (bfd_get_target (file), "mmo") == 0)
	print_width = 64;
      else
	print_width = 32;
    }
}