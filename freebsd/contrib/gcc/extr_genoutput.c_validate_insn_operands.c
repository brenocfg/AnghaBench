#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct data {int n_operands; int /*<<< orphan*/  lineno; TYPE_1__* operand; } ;
struct TYPE_2__ {scalar_t__ seen; } ;

/* Variables and functions */
 int have_error ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
validate_insn_operands (struct data *d)
{
  int i;

  for (i = 0; i < d->n_operands; ++i)
    if (d->operand[i].seen == 0)
      {
	message_with_line (d->lineno, "missing operand %d", i);
	have_error = 1;
      }
}