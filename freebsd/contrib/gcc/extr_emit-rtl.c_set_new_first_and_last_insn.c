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
typedef  void* rtx ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_UID (void*) ; 
 scalar_t__ MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 void* NEXT_INSN (void*) ; 
 scalar_t__ cur_insn_uid ; 
 void* first_insn ; 
 void* last_insn ; 

void
set_new_first_and_last_insn (rtx first, rtx last)
{
  rtx insn;

  first_insn = first;
  last_insn = last;
  cur_insn_uid = 0;

  for (insn = first; insn; insn = NEXT_INSN (insn))
    cur_insn_uid = MAX (cur_insn_uid, INSN_UID (insn));

  cur_insn_uid++;
}