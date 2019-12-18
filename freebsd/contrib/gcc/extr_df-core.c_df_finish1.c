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
struct df {int num_problems_defined; TYPE_2__** problems_in_order; } ;
struct TYPE_4__ {TYPE_1__* problem; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_fun ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct df*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
df_finish1 (struct df *df)
{
  int i;

  for (i = 0; i < df->num_problems_defined; i++)
    df->problems_in_order[i]->problem->free_fun (df->problems_in_order[i]); 

  free (df);
}