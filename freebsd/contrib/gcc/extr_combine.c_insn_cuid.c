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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INSN_CUID (scalar_t__) ; 
 scalar_t__ INSN_UID (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NONJUMP_INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ max_uid_cuid ; 

__attribute__((used)) static int
insn_cuid (rtx insn)
{
  while (insn != 0 && INSN_UID (insn) > max_uid_cuid
	 && NONJUMP_INSN_P (insn) && GET_CODE (PATTERN (insn)) == USE)
    insn = NEXT_INSN (insn);

  gcc_assert (INSN_UID (insn) <= max_uid_cuid);

  return INSN_CUID (insn);
}