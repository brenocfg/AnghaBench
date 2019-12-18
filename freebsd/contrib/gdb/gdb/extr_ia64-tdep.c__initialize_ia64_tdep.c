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
 int /*<<< orphan*/  bfd_arch_ia64 ; 
 int /*<<< orphan*/  ia64_gdbarch_init ; 
 int /*<<< orphan*/  register_gdbarch_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_initialize_ia64_tdep (void)
{
  register_gdbarch_init (bfd_arch_ia64, ia64_gdbarch_init);
}