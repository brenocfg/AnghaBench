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
struct loop {int dummy; } ;
struct TYPE_2__ {unsigned int num; struct loop** parray; } ;

/* Variables and functions */
 TYPE_1__* current_loops ; 
 int /*<<< orphan*/  tree_if_conversion (struct loop*,int) ; 

__attribute__((used)) static unsigned int
main_tree_if_conversion (void)
{
  unsigned i, loop_num;
  struct loop *loop;

  if (!current_loops)
    return 0;

  loop_num = current_loops->num;
  for (i = 0; i < loop_num; i++)
    {
      loop =  current_loops->parray[i];
      if (!loop)
      continue;

      tree_if_conversion (loop, true);
    }
  return 0;
}