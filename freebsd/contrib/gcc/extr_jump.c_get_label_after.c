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
typedef  int /*<<< orphan*/  LABEL_NUSES ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_P (scalar_t__) ; 
 int /*<<< orphan*/  emit_label_after (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ next_nonnote_insn (scalar_t__) ; 

rtx
get_label_after (rtx insn)
{
  rtx label;

  /* Find an existing label at this point
     or make a new one if there is none.  */
  label = next_nonnote_insn (insn);

  if (label == 0 || !LABEL_P (label))
    {
      label = gen_label_rtx ();
      emit_label_after (label, insn);
      LABEL_NUSES (label) = 0;
    }
  return label;
}