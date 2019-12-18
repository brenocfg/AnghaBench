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
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  unshare_all_rtl_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
unshare_all_rtl (void)
{
  unshare_all_rtl_1 (current_function_decl, get_insns ());
  return 0;
}