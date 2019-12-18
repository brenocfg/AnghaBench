#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cgen_parse_operand_fn ;
struct TYPE_3__ {int /*<<< orphan*/  parse_operand_fn; } ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */

void
cgen_set_parse_operand_fn (CGEN_CPU_DESC cd, cgen_parse_operand_fn fn)
{
  cd->parse_operand_fn = fn;
}