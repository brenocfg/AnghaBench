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
struct insn_operand_data {int (* predicate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {struct insn_operand_data* operand; } ;

/* Variables and functions */
 TYPE_1__* insn_data ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safe_insn_predicate (int code, int operand, rtx x)
{
  const struct insn_operand_data *op_data;

  if (code < 0)
    return true;

  op_data = &insn_data[code].operand[operand];
  if (op_data->predicate == NULL)
    return true;

  return op_data->predicate (x, op_data->mode);
}