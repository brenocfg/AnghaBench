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
 int /*<<< orphan*/  find_invariant_insn (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  record_uses (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_invariants_insn (rtx insn, bool always_reached, bool always_executed)
{
  find_invariant_insn (insn, always_reached, always_executed);
  record_uses (insn);
}