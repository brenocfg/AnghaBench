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
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_EQUAL ; 
 scalar_t__ REG_EQUIV ; 
 int /*<<< orphan*/ * REG_NOTES (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_NOTE_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ single_set (int /*<<< orphan*/ *) ; 

rtx
find_reg_equal_equiv_note (rtx insn)
{
  rtx link;

  if (!INSN_P (insn))
    return 0;
  for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
    if (REG_NOTE_KIND (link) == REG_EQUAL
	|| REG_NOTE_KIND (link) == REG_EQUIV)
      {
	if (single_set (insn) == 0)
	  return 0;
	return link;
      }
  return NULL;
}