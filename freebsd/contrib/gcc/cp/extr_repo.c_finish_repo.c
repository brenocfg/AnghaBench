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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DECL_ASSEMBLER_NAME (scalar_t__) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ IDENTIFIER_REPO_CHOSEN (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* flag_random_seed ; 
 int /*<<< orphan*/  flag_use_repository ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* getenv (char*) ; 
 char* getpwd () ; 
 char* main_input_filename ; 
 scalar_t__ pending_repo ; 
 int /*<<< orphan*/ * reopen_repo_file_for_write () ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

void
finish_repo (void)
{
  tree t;
  char *dir, *args;
  FILE *repo_file;

  if (!flag_use_repository)
    return;

  if (errorcount || sorrycount)
    return;

  repo_file = reopen_repo_file_for_write ();
  if (repo_file == 0)
    goto out;

  fprintf (repo_file, "M %s\n", main_input_filename);
  dir = getpwd ();
  fprintf (repo_file, "D %s\n", dir);
  args = getenv ("COLLECT_GCC_OPTIONS");
  if (args)
    {
      fprintf (repo_file, "A %s", args);
      /* If -frandom-seed is not among the ARGS, then add the value
	 that we chose.  That will ensure that the names of types from
	 anonymous namespaces will get the same mangling when this
	 file is recompiled.  */
      if (!strstr (args, "'-frandom-seed="))
	fprintf (repo_file, " '-frandom-seed=%s'", flag_random_seed);
      fprintf (repo_file, "\n");
    }

  for (t = pending_repo; t; t = TREE_CHAIN (t))
    {
      tree val = TREE_VALUE (t);
      tree name = DECL_ASSEMBLER_NAME (val);
      char type = IDENTIFIER_REPO_CHOSEN (name) ? 'C' : 'O';
      fprintf (repo_file, "%c %s\n", type, IDENTIFIER_POINTER (name));
    }

 out:
  if (repo_file)
    fclose (repo_file);
}