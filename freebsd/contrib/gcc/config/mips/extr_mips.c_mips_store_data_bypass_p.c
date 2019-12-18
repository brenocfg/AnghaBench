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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC_VOLATILE ; 
 int /*<<< orphan*/  store_data_bypass_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mips_store_data_bypass_p (rtx out_insn, rtx in_insn)
{
  if (GET_CODE (PATTERN (in_insn)) == UNSPEC_VOLATILE)
    return false;

  return ! store_data_bypass_p (out_insn, in_insn);
}