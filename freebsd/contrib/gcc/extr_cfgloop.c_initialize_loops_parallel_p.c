#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct loops {unsigned int num; struct loop** parray; } ;
struct loop {int parallel_p; } ;

/* Variables and functions */

__attribute__((used)) static void
initialize_loops_parallel_p (struct loops *loops)
{
  unsigned int i;

  for (i = 0; i < loops->num; i++)
    {
      struct loop *loop = loops->parray[i];
      loop->parallel_p = true;
    }
}