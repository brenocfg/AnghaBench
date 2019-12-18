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
 int ECF_MAY_BE_ALLOCA ; 
 int ECF_RETURNS_TWICE ; 
 int call_expr_flags (int /*<<< orphan*/ ) ; 
 int current_function_calls_alloca ; 
 int current_function_calls_setjmp ; 

void
notice_special_calls (tree t)
{
  int flags = call_expr_flags (t);

  if (flags & ECF_MAY_BE_ALLOCA)
    current_function_calls_alloca = true;
  if (flags & ECF_RETURNS_TWICE)
    current_function_calls_setjmp = true;
}