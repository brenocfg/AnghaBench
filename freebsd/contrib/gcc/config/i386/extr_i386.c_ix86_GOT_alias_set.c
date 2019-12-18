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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int new_alias_set () ; 

__attribute__((used)) static HOST_WIDE_INT
ix86_GOT_alias_set (void)
{
  static HOST_WIDE_INT set = -1;
  if (set == -1)
    set = new_alias_set ();
  return set;
}