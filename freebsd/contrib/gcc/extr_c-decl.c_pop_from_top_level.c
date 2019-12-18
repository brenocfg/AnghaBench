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

/* Variables and functions */
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  current_scope ; 
 int /*<<< orphan*/  save_current_function_decl ; 
 int /*<<< orphan*/  save_current_scope ; 

void
pop_from_top_level (void)
{
  current_scope = save_current_scope;
  current_function_decl = save_current_function_decl;
}