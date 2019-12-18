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
 void* NEXT_INSN (void*) ; 
 void* first_insn ; 
 void* last_insn ; 
 int /*<<< orphan*/  start_sequence () ; 

void
push_to_sequence (rtx first)
{
  rtx last;

  start_sequence ();

  for (last = first; last && NEXT_INSN (last); last = NEXT_INSN (last));

  first_insn = first;
  last_insn = last;
}