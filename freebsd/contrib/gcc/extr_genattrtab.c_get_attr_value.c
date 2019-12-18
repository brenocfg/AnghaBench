#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct attr_value {scalar_t__ has_asm_insn; scalar_t__ num_insns; TYPE_2__* first_insn; struct attr_value* next; int /*<<< orphan*/  value; } ;
struct attr_desc {struct attr_value* first_value; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* def; } ;
struct TYPE_3__ {size_t insn_code; } ;

/* Variables and functions */
 scalar_t__ compares_alternatives_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int* insn_alternatives ; 
 int /*<<< orphan*/  make_canonical (struct attr_desc*,int /*<<< orphan*/ ) ; 
 struct attr_value* oballoc (int) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct attr_value *
get_attr_value (rtx value, struct attr_desc *attr, int insn_code)
{
  struct attr_value *av;
  int num_alt = 0;

  value = make_canonical (attr, value);
  if (compares_alternatives_p (value))
    {
      if (insn_code < 0 || insn_alternatives == NULL)
	fatal ("(eq_attr \"alternatives\" ...) used in non-insn context");
      else
	num_alt = insn_alternatives[insn_code];
    }

  for (av = attr->first_value; av; av = av->next)
    if (rtx_equal_p (value, av->value)
	&& (num_alt == 0 || av->first_insn == NULL
	    || insn_alternatives[av->first_insn->def->insn_code]))
      return av;

  av = oballoc (sizeof (struct attr_value));
  av->value = value;
  av->next = attr->first_value;
  attr->first_value = av;
  av->first_insn = NULL;
  av->num_insns = 0;
  av->has_asm_insn = 0;

  return av;
}