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
 int /*<<< orphan*/  N_SO ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  generate_asm_file (int /*<<< orphan*/ ,char*) ; 
 char* getpwd () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ use_gnu_debug_info_extensions ; 

void
stabs_generate_asm_file (void)
{
  char *file;
  unsigned int lineno;

  as_where (&file, &lineno);
  if (use_gnu_debug_info_extensions)
    {
      char *dir, *dir2;

      dir = getpwd ();
      dir2 = alloca (strlen (dir) + 2);
      sprintf (dir2, "%s%s", dir, "/");
      generate_asm_file (N_SO, dir2);
    }
  generate_asm_file (N_SO, file);
}