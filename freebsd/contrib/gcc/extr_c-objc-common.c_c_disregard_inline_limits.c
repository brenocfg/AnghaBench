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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DECLARED_INLINE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_really_no_inline ; 
 int /*<<< orphan*/ * lookup_attribute (char*,int /*<<< orphan*/ ) ; 

int
c_disregard_inline_limits (tree fn)
{
  if (lookup_attribute ("always_inline", DECL_ATTRIBUTES (fn)) != NULL)
    return 1;

  return (!flag_really_no_inline && DECL_DECLARED_INLINE_P (fn)
	  && DECL_EXTERNAL (fn));
}