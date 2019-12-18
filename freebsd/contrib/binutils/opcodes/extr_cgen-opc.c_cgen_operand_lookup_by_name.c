#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int num_entries; TYPE_2__** entries; } ;
struct TYPE_8__ {TYPE_1__ operand_table; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ CGEN_OPERAND ;
typedef  TYPE_3__* CGEN_CPU_DESC ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const CGEN_OPERAND *
cgen_operand_lookup_by_name (CGEN_CPU_DESC cd, const char *name)
{
  unsigned int i;
  const CGEN_OPERAND **op = cd->operand_table.entries;

  for (i = 0; i < cd->operand_table.num_entries; ++i)
    if (op[i] && strcmp (name, op[i]->name) == 0)
      return op[i];

  return NULL;
}