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
 scalar_t__ DEBUG_MANGLE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/  const) ; 
 scalar_t__ TYPE_DECL ; 
 char* finish_mangling (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_mangled_name (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
mangle_decl_string (const tree decl)
{
  const char *result;

  start_mangling (decl, /*ident_p=*/true);

  if (TREE_CODE (decl) == TYPE_DECL)
    write_type (TREE_TYPE (decl));
  else
    write_mangled_name (decl, true);

  result = finish_mangling (/*warn=*/true);
  if (DEBUG_MANGLE)
    fprintf (stderr, "mangle_decl_string = '%s'\n\n", result);
  return result;
}