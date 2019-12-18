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
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/  const) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_mangling (int) ; 
 int /*<<< orphan*/  get_identifier_nocopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_mangling (int /*<<< orphan*/  const,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  write_name (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 

tree
mangle_guard_variable (const tree variable)
{
  start_mangling (variable, /*ident_p=*/true);
  write_string ("_ZGV");
  if (strncmp (IDENTIFIER_POINTER (DECL_NAME (variable)), "_ZGR", 4) == 0)
    /* The name of a guard variable for a reference temporary should refer
       to the reference, not the temporary.  */
    write_string (IDENTIFIER_POINTER (DECL_NAME (variable)) + 4);
  else
    write_name (variable, /*ignore_local_scope=*/0);
  return get_identifier_nocopy (finish_mangling (/*warn=*/false));
}