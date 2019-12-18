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
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  mark_blocks_with_used_vars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
mark_used_blocks (void)
{  
  mark_blocks_with_used_vars (DECL_INITIAL (current_function_decl));
  return 0;
}