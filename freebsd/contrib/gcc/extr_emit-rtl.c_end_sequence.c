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
struct sequence_stack {struct sequence_stack* next; int /*<<< orphan*/  last; int /*<<< orphan*/  first; } ;

/* Variables and functions */
 int /*<<< orphan*/  first_insn ; 
 struct sequence_stack* free_sequence_stack ; 
 int /*<<< orphan*/  last_insn ; 
 int /*<<< orphan*/  memset (struct sequence_stack*,int /*<<< orphan*/ ,int) ; 
 struct sequence_stack* seq_stack ; 

void
end_sequence (void)
{
  struct sequence_stack *tem = seq_stack;

  first_insn = tem->first;
  last_insn = tem->last;
  seq_stack = tem->next;

  memset (tem, 0, sizeof (*tem));
  tem->next = free_sequence_stack;
  free_sequence_stack = tem;
}