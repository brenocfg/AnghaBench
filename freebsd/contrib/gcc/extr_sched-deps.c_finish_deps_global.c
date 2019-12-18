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
 int /*<<< orphan*/  FREE_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_pending_clobbers ; 
 int /*<<< orphan*/  reg_pending_sets ; 
 int /*<<< orphan*/  reg_pending_uses ; 

void
finish_deps_global (void)
{
  FREE_REG_SET (reg_pending_sets);
  FREE_REG_SET (reg_pending_clobbers);
  FREE_REG_SET (reg_pending_uses);
}