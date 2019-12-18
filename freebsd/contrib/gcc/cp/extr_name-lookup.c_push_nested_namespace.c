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

/* Variables and functions */
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  push_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_to_top_level () ; 

void
push_nested_namespace (tree ns)
{
  if (ns == global_namespace)
    push_to_top_level ();
  else
    {
      push_nested_namespace (CP_DECL_CONTEXT (ns));
      push_namespace (DECL_NAME (ns));
    }
}