#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bpstat ;
struct TYPE_4__ {int /*<<< orphan*/  commands; int /*<<< orphan*/ * old_val; struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_command_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
bpstat_clear (bpstat *bsp)
{
  bpstat p;
  bpstat q;

  if (bsp == 0)
    return;
  p = *bsp;
  while (p != NULL)
    {
      q = p->next;
      if (p->old_val != NULL)
	value_free (p->old_val);
      free_command_lines (&p->commands);
      xfree (p);
      p = q;
    }
  *bsp = NULL;
}