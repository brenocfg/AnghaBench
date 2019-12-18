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
typedef  scalar_t__ t ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

void
pp_c_tree_decl_identifier (c_pretty_printer *pp, tree t)
{
  const char *name;

  gcc_assert (DECL_P (t));

  if (DECL_NAME (t))
    name = IDENTIFIER_POINTER (DECL_NAME (t));
  else
    {
      static char xname[8];
      sprintf (xname, "<U%4x>", ((unsigned)((unsigned long)(t) & 0xffff)));
      name = xname;
    }

  pp_c_identifier (pp, name);
}