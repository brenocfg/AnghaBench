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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_decl_specifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pp_cxx_parameter_declaration (cxx_pretty_printer *pp, tree t)
{
  pp_cxx_decl_specifier_seq (pp, t);
  if (TYPE_P (t))
    pp_cxx_abstract_declarator (pp, t);
  else
    pp_cxx_declarator (pp, t);
}