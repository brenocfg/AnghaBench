#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct convert_optab {int dummy; } ;
typedef  TYPE_2__* convert_optab ;
struct TYPE_6__ {TYPE_1__** handlers; } ;
struct TYPE_5__ {scalar_t__ libfunc; int /*<<< orphan*/  insn_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_FOR_nothing ; 
 int NUM_MACHINE_MODES ; 
 TYPE_2__* ggc_alloc (int) ; 

__attribute__((used)) static convert_optab
new_convert_optab (void)
{
  int i, j;
  convert_optab op = ggc_alloc (sizeof (struct convert_optab));
  for (i = 0; i < NUM_MACHINE_MODES; i++)
    for (j = 0; j < NUM_MACHINE_MODES; j++)
      {
	op->handlers[i][j].insn_code = CODE_FOR_nothing;
	op->handlers[i][j].libfunc = 0;
      }
  return op;
}