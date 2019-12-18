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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ constrain_operands (int) ; 
 int /*<<< orphan*/  delete_insns_since (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * emit_insn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_insn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_last_insn () ; 
 int recog_memoized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rtx
emit_insn_if_valid_for_reload (rtx insn)
{
  rtx last = get_last_insn ();
  int code;

  insn = emit_insn (insn);
  code = recog_memoized (insn);

  if (code >= 0)
    {
      extract_insn (insn);
      /* We want constrain operands to treat this insn strictly in its
	 validity determination, i.e., the way it would after reload has
	 completed.  */
      if (constrain_operands (1))
	return insn;
    }

  delete_insns_since (last);
  return NULL;
}