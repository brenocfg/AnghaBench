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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  current_scope ; 
 int /*<<< orphan*/  file_scope ; 
 int /*<<< orphan*/  save_current_function_decl ; 
 int /*<<< orphan*/  save_current_scope ; 

void
push_to_top_level (void)
{
  save_current_scope = current_scope;
  save_current_function_decl = current_function_decl;
  current_scope = file_scope;
  current_function_decl = NULL_TREE;
}