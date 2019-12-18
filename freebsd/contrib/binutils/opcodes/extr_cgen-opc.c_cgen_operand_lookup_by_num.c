#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  const** entries; } ;
struct TYPE_5__ {TYPE_1__ operand_table; } ;
typedef  int /*<<< orphan*/  CGEN_OPERAND ;
typedef  TYPE_2__* CGEN_CPU_DESC ;

/* Variables and functions */

const CGEN_OPERAND *
cgen_operand_lookup_by_num (CGEN_CPU_DESC cd, int opnum)
{
  return cd->operand_table.entries[opnum];
}