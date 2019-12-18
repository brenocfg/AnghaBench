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
 scalar_t__ NOTE_LINE_NUMBER (scalar_t__) ; 
 scalar_t__ NOTE_P (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 scalar_t__ no_line_numbers ; 

__attribute__((used)) static rtx
find_line_note (rtx insn)
{
  if (no_line_numbers)
    return 0;

  for (; insn; insn = PREV_INSN (insn))
    if (NOTE_P (insn)
	&& NOTE_LINE_NUMBER (insn) >= 0)
      break;

  return insn;
}