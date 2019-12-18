#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_6__ {int /*<<< orphan*/ * enclosing_scope; } ;
typedef  TYPE_1__ cxx_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/ * DECL_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_CONTEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_template_keyword_if_needed (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_nested_name_specifier (cxx_pretty_printer *pp, tree t)
{
  if (t != NULL && t != pp->enclosing_scope)
    {
      tree scope = TYPE_P (t) ? TYPE_CONTEXT (t) : DECL_CONTEXT (t);
      pp_cxx_nested_name_specifier (pp, scope);
      pp_cxx_template_keyword_if_needed (pp, scope, t);
      pp_cxx_unqualified_id (pp, t);
      pp_cxx_colon_colon (pp);
    }
}