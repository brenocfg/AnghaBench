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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i386nbsd_aout_regset_from_core_section ; 
 int /*<<< orphan*/  i386nbsd_init_abi (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_regset_from_core_section (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i386nbsdaout_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  i386nbsd_init_abi (info, gdbarch);

  /* NetBSD a.out has a single register set.  */
  set_gdbarch_regset_from_core_section
    (gdbarch, i386nbsd_aout_regset_from_core_section);
}