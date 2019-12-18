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
struct function {scalar_t__ decl; struct function* outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_unreachable () ; 
 struct function* outer_function_chain ; 

struct function *
find_function_data (tree decl)
{
  struct function *p;

  for (p = outer_function_chain; p; p = p->outer)
    if (p->decl == decl)
      return p;

  gcc_unreachable ();
}