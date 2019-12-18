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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ host_integerp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_quote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_scalar (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  tree_low_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_type_node ; 

__attribute__((used)) static void
pp_c_character_constant (c_pretty_printer *pp, tree c)
{
  tree type = TREE_TYPE (c);
  if (type == wchar_type_node)
    pp_character (pp, 'L');
  pp_quote (pp);
  if (host_integerp (c, TYPE_UNSIGNED (type)))
    pp_c_char (pp, tree_low_cst (c, TYPE_UNSIGNED (type)));
  else
    pp_scalar (pp, "\\x%x", (unsigned) TREE_INT_CST_LOW (c));
  pp_quote (pp);
}