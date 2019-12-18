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
typedef  scalar_t__ DECL_CONTEXT ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ DECL_PENDING_INLINE_INFO (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 

__attribute__((used)) static void
fixup_pending_inline (tree fn)
{
  if (DECL_PENDING_INLINE_INFO (fn))
    {
      tree args = DECL_ARGUMENTS (fn);
      while (args)
	{
	  DECL_CONTEXT (args) = fn;
	  args = TREE_CHAIN (args);
	}
    }
}