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
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  record_vars_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
record_vars (tree vars)
{
  record_vars_into (vars, current_function_decl);
}