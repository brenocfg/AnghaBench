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
struct constant_pool {int size; struct constant* execute; } ;
struct constant {struct constant* next; int /*<<< orphan*/  label; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
s390_add_execute (struct constant_pool *pool, rtx insn)
{
  struct constant *c;

  for (c = pool->execute; c != NULL; c = c->next)
    if (INSN_UID (insn) == INSN_UID (c->value))
      break;

  if (c == NULL)
    {
      c = (struct constant *) xmalloc (sizeof *c);
      c->value = insn;
      c->label = gen_label_rtx ();
      c->next = pool->execute;
      pool->execute = c;
      pool->size += 6;
    }
}