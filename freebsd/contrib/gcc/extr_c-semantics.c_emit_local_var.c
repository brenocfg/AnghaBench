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
 scalar_t__ DECL_HARD_REGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL_SET_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rest_of_decl_compilation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
emit_local_var (tree decl)
{
  /* Create RTL for this variable.  */
  if (!DECL_RTL_SET_P (decl))
    {
      if (DECL_HARD_REGISTER (decl))
	/* The user specified an assembler name for this variable.
	   Set that up now.  */
	rest_of_decl_compilation (decl, 0, 0);
      else
	expand_decl (decl);
    }
}