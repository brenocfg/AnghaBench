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
struct dataflow {int flags; TYPE_1__* problem; } ;
struct TYPE_2__ {int changeable_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 

int 
df_set_flags (struct dataflow *dflow, int mask)
{
  int old_flags = dflow->flags;

  gcc_assert (!(mask & (~dflow->problem->changeable_flags)));

  dflow->flags |= mask;

  return old_flags;
}