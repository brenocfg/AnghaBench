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
struct constant_pool {int /*<<< orphan*/  label; struct constant* execute; } ;
struct constant {int /*<<< orphan*/  label; int /*<<< orphan*/  value; struct constant* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  gcc_assert (struct constant*) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
s390_find_execute (struct constant_pool *pool, rtx insn)
{
  struct constant *c;
  rtx offset;

  for (c = pool->execute; c != NULL; c = c->next)
    if (INSN_UID (insn) == INSN_UID (c->value))
      break;

  gcc_assert (c);

  offset = gen_rtx_MINUS (Pmode, gen_rtx_LABEL_REF (Pmode, c->label),
				 gen_rtx_LABEL_REF (Pmode, pool->label));
  offset = gen_rtx_CONST (Pmode, offset);
  return offset;
}