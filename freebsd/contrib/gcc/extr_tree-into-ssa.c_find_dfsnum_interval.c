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
struct dom_dfsnum {unsigned int dfs_num; int bb_index; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
find_dfsnum_interval (struct dom_dfsnum *defs, unsigned n, unsigned s)
{
  unsigned f = 0, t = n, m;

  while (t > f + 1)
    {
      m = (f + t) / 2;
      if (defs[m].dfs_num <= s)
	f = m;
      else
	t = m;
    }

  return defs[f].bb_index;
}