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
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ is_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
namespace_ancestor (tree ns1, tree ns2)
{
  timevar_push (TV_NAME_LOOKUP);
  if (is_ancestor (ns1, ns2))
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, ns1);
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP,
			  namespace_ancestor (CP_DECL_CONTEXT (ns1), ns2));
}