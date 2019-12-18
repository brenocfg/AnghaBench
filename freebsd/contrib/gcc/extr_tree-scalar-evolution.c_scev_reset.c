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
struct loop {int /*<<< orphan*/  nb_iterations; } ;
struct TYPE_2__ {unsigned int num; struct loop** parray; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 TYPE_1__* current_loops ; 
 int /*<<< orphan*/  htab_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

void
scev_reset (void)
{
  unsigned i;
  struct loop *loop;

  if (!scalar_evolution_info || !current_loops)
    return;

  htab_empty (scalar_evolution_info);
  for (i = 1; i < current_loops->num; i++)
    {
      loop = current_loops->parray[i];
      if (loop)
	loop->nb_iterations = NULL_TREE;
    }
}