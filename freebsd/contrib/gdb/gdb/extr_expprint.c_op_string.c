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
struct op_print {scalar_t__ opcode; char* string; } ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
struct TYPE_2__ {struct op_print* la_op_print_tab; } ;

/* Variables and functions */
 scalar_t__ OP_NULL ; 
 TYPE_1__* current_language ; 

char *
op_string (enum exp_opcode op)
{
  int tem;
  const struct op_print *op_print_tab;

  op_print_tab = current_language->la_op_print_tab;
  for (tem = 0; op_print_tab[tem].opcode != OP_NULL; tem++)
    if (op_print_tab[tem].opcode == op)
      return op_print_tab[tem].string;
  return NULL;
}