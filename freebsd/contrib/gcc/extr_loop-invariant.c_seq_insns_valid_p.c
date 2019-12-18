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
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ insn_invalid_p (scalar_t__) ; 

__attribute__((used)) static bool
seq_insns_valid_p (rtx seq)
{
  rtx x;

  for (x = seq; x; x = NEXT_INSN (x))
    if (insn_invalid_p (x))
      return false;

  return true;
}