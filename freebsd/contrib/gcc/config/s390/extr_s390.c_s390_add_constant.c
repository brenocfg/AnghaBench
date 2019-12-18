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
struct constant_pool {int /*<<< orphan*/  size; struct constant** constants; } ;
struct constant {struct constant* next; int /*<<< orphan*/  label; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_SIZE (int) ; 
 int NR_C_MODES ; 
 int* constant_modes ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
s390_add_constant (struct constant_pool *pool, rtx val, enum machine_mode mode)
{
  struct constant *c;
  int i;

  for (i = 0; i < NR_C_MODES; i++)
    if (constant_modes[i] == mode)
      break;
  gcc_assert (i != NR_C_MODES);

  for (c = pool->constants[i]; c != NULL; c = c->next)
    if (rtx_equal_p (val, c->value))
      break;

  if (c == NULL)
    {
      c = (struct constant *) xmalloc (sizeof *c);
      c->value = val;
      c->label = gen_label_rtx ();
      c->next = pool->constants[i];
      pool->constants[i] = c;
      pool->size += GET_MODE_SIZE (mode);
    }
}