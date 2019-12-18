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
struct eh_region {int may_contain_throw; struct eh_region* outer; } ;

/* Variables and functions */

void
note_eh_region_may_contain_throw (struct eh_region *region)
{
  while (region && !region->may_contain_throw)
    {
      region->may_contain_throw = 1;
      region = region->outer;
    }
}