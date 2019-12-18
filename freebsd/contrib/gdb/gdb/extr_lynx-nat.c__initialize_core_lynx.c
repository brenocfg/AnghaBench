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
 int /*<<< orphan*/  add_core_fns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lynx_core_fns ; 

void
_initialize_core_lynx (void)
{
  add_core_fns (&lynx_core_fns);
}