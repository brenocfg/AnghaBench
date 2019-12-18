#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_10__ {int /*<<< orphan*/ * tokens; } ;
struct TYPE_11__ {unsigned int paramc; scalar_t__ fun_like; scalar_t__ variadic; scalar_t__* params; unsigned int count; TYPE_2__ exp; } ;
typedef  TYPE_3__ cpp_macro ;
struct TYPE_9__ {TYPE_3__* macro; } ;
struct TYPE_12__ {int flags; TYPE_1__ value; } ;
typedef  TYPE_4__ cpp_hashnode ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NODE_WARN ; 
 int /*<<< orphan*/  _cpp_equiv_tokens (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _cpp_expansions_different_trad (TYPE_3__ const*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  traditional ; 

__attribute__((used)) static bool
warn_of_redefinition (cpp_reader *pfile, const cpp_hashnode *node,
		      const cpp_macro *macro2)
{
  const cpp_macro *macro1;
  unsigned int i;

  /* Some redefinitions need to be warned about regardless.  */
  if (node->flags & NODE_WARN)
    return true;

  /* Redefinition of a macro is allowed if and only if the old and new
     definitions are the same.  (6.10.3 paragraph 2).  */
  macro1 = node->value.macro;

  /* Don't check count here as it can be different in valid
     traditional redefinitions with just whitespace differences.  */
  if (macro1->paramc != macro2->paramc
      || macro1->fun_like != macro2->fun_like
      || macro1->variadic != macro2->variadic)
    return true;

  /* Check parameter spellings.  */
  for (i = 0; i < macro1->paramc; i++)
    if (macro1->params[i] != macro2->params[i])
      return true;

  /* Check the replacement text or tokens.  */
  if (CPP_OPTION (pfile, traditional))
    return _cpp_expansions_different_trad (macro1, macro2);

  if (macro1->count != macro2->count)
    return true;

  for (i = 0; i < macro1->count; i++)
    if (!_cpp_equiv_tokens (&macro1->exp.tokens[i], &macro2->exp.tokens[i]))
      return true;

  return false;
}