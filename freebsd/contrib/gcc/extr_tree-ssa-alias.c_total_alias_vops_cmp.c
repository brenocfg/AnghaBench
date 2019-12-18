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
struct alias_map_d {long total_alias_vops; } ;

/* Variables and functions */

__attribute__((used)) static int
total_alias_vops_cmp (const void *p, const void *q)
{
  const struct alias_map_d **p1 = (const struct alias_map_d **)p;
  const struct alias_map_d **p2 = (const struct alias_map_d **)q;
  long n1 = (*p1)->total_alias_vops;
  long n2 = (*p2)->total_alias_vops;

  /* We want to sort in descending order.  */
  return (n1 > n2 ? -1 : (n1 == n2) ? 0 : 1);
}