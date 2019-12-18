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
typedef  int /*<<< orphan*/  file ;

/* Variables and functions */
 int /*<<< orphan*/  file_exists (char const*) ; 
 int /*<<< orphan*/ * file_hash_lookup (char const*) ; 
 int /*<<< orphan*/ * file_stack ; 
 char* frob_extension (char*,char*) ; 
 int /*<<< orphan*/  read_repo_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recompile_files () ; 
 int /*<<< orphan*/ * symbol_stack ; 

__attribute__((used)) static int
read_repo_files (char **object_lst)
{
  char **object = object_lst;

  for (; *object; object++)
    {
      const char *p;
      file *f;

      /* Don't bother trying for ld flags.  */
      if (*object[0] == '-')
	continue;

      p = frob_extension (*object, ".rpo");

      if (! file_exists (p))
	continue;

      f = file_hash_lookup (p);

      read_repo_file (f);
    }

  if (file_stack != NULL && ! recompile_files ())
    return 0;

  return (symbol_stack != NULL);
}