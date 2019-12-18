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
struct loops {int dummy; } ;
struct loop {struct loop* next; struct loop* inner; } ;

/* Variables and functions */
 struct loop* duplicate_loop (struct loops*,struct loop*,struct loop*) ; 

__attribute__((used)) static void
duplicate_subloops (struct loops *loops, struct loop *loop, struct loop *target)
{
  struct loop *aloop, *cloop;

  for (aloop = loop->inner; aloop; aloop = aloop->next)
    {
      cloop = duplicate_loop (loops, aloop, target);
      duplicate_subloops (loops, aloop, cloop);
    }
}