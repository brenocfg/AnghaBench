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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ canon_reg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_change (scalar_t__,scalar_t__*,scalar_t__,int) ; 

__attribute__((used)) static void
validate_canon_reg (rtx *xloc, rtx insn)
{
  rtx new = canon_reg (*xloc, insn);

  /* If replacing pseudo with hard reg or vice versa, ensure the
     insn remains valid.  Likewise if the insn has MATCH_DUPs.  */
  if (insn != 0 && new != 0)
    validate_change (insn, xloc, new, 1);
  else
    *xloc = new;
}