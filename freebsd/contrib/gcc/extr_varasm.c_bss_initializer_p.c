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
 int /*<<< orphan*/ * DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_READONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * error_mark_node ; 
 scalar_t__ flag_zero_initialized_in_bss ; 
 scalar_t__ initializer_zerop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
bss_initializer_p (tree decl)
{
  return (DECL_INITIAL (decl) == NULL
	  || DECL_INITIAL (decl) == error_mark_node
	  || (flag_zero_initialized_in_bss
	      /* Leave constant zeroes in .rodata so they
		 can be shared.  */
	      && !TREE_READONLY (decl)
	      && initializer_zerop (DECL_INITIAL (decl))));
}