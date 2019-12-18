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
struct loop {struct loop* next; struct loop* inner; } ;

/* Variables and functions */

unsigned
get_loop_level (const struct loop *loop)
{
  const struct loop *ploop;
  unsigned mx = 0, l;

  for (ploop = loop->inner; ploop; ploop = ploop->next)
    {
      l = get_loop_level (ploop);
      if (l >= mx)
	mx = l + 1;
    }
  return mx;
}