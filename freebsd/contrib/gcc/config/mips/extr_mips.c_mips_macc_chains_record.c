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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ get_attr_may_clobber_hilo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_macc_chains_last_hilo ; 

__attribute__((used)) static void
mips_macc_chains_record (rtx insn)
{
  if (get_attr_may_clobber_hilo (insn))
    mips_macc_chains_last_hilo = insn;
}