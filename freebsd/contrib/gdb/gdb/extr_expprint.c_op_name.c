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
struct expression {TYPE_2__* language_defn; } ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
struct TYPE_4__ {TYPE_1__* la_exp_desc; } ;
struct TYPE_3__ {char* (* op_name ) (int) ;} ;

/* Variables and functions */
 char* stub1 (int) ; 

__attribute__((used)) static char *
op_name (struct expression *exp, enum exp_opcode opcode)
{
  return exp->language_defn->la_exp_desc->op_name (opcode);
}