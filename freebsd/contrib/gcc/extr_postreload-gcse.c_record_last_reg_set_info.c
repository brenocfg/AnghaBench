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
 int /*<<< orphan*/  INSN_CUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reg_avail_info ; 

__attribute__((used)) static inline void
record_last_reg_set_info (rtx insn, int regno)
{
  reg_avail_info[regno] = INSN_CUID (insn);
}