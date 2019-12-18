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
 int TFF_CLASS_KEY_OR_ENUM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPENAME_TYPE ; 
 int /*<<< orphan*/  TYPENAME_TYPE_FULLNAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_typename (tree t, int flags)
{
  tree ctx = TYPE_CONTEXT (t);

  if (TREE_CODE (ctx) == TYPENAME_TYPE)
    dump_typename (ctx, flags);
  else
    dump_type (ctx, flags & ~TFF_CLASS_KEY_OR_ENUM);
  pp_cxx_colon_colon (cxx_pp);
  dump_decl (TYPENAME_TYPE_FULLNAME (t), flags);
}