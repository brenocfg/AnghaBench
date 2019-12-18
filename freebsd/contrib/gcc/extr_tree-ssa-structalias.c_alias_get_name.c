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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int asprintf (char**,char*,char const*,...) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_name (int /*<<< orphan*/ ) ; 
 char* ggc_strdup (char*) ; 

__attribute__((used)) static const char *
alias_get_name (tree decl)
{
  const char *res = get_name (decl);
  char *temp;
  int num_printed = 0;

  if (res != NULL)
    return res;

  res = "NULL";
  if (!dump_file)
    return res;

  if (TREE_CODE (decl) == SSA_NAME)
    {
      num_printed = asprintf (&temp, "%s_%u",
			      alias_get_name (SSA_NAME_VAR (decl)),
			      SSA_NAME_VERSION (decl));
    }
  else if (DECL_P (decl))
    {
      num_printed = asprintf (&temp, "D.%u", DECL_UID (decl));
    }
  if (num_printed > 0)
    {
      res = ggc_strdup (temp);
      free (temp);
    }
  return res;
}