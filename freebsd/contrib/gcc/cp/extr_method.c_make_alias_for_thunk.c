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
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_syntax_only ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  make_alias_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thunk_labelno ; 

__attribute__((used)) static tree
make_alias_for_thunk (tree function)
{
  tree alias;
  char buf[256];

  ASM_GENERATE_INTERNAL_LABEL (buf, "LTHUNK", thunk_labelno);
  thunk_labelno++;

  alias = make_alias_for (function, get_identifier (buf));

  if (!flag_syntax_only)
    assemble_alias (alias, DECL_ASSEMBLER_NAME (function));

  return alias;
}