#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  first_frag; } ;
struct TYPE_3__ {scalar_t__ first_fixup; int /*<<< orphan*/ * sizes; int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  RELAX_ENCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ mips_macro_warning ; 
 TYPE_1__ mips_relax ; 
 int /*<<< orphan*/  rs_machine_dependent ; 

__attribute__((used)) static void
relax_close_frag (void)
{
  mips_macro_warning.first_frag = frag_now;
  frag_var (rs_machine_dependent, 0, 0,
	    RELAX_ENCODE (mips_relax.sizes[0], mips_relax.sizes[1]),
	    mips_relax.symbol, 0, (char *) mips_relax.first_fixup);

  memset (&mips_relax.sizes, 0, sizeof (mips_relax.sizes));
  mips_relax.first_fixup = 0;
}