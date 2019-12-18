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
typedef  size_t operand_type ;
typedef  int /*<<< orphan*/  argtype ;
struct TYPE_2__ {int /*<<< orphan*/  arg_type; } ;

/* Variables and functions */
 size_t MAX_OPRD ; 
 TYPE_1__* cr16_optab ; 
 int /*<<< orphan*/  nullargs ; 

__attribute__((used)) static argtype
get_optype (operand_type op)
{
  if (op < MAX_OPRD)
    return cr16_optab[op].arg_type;
  else
    return nullargs;
}