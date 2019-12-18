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

/* Variables and functions */

__attribute__((used)) inline static int
number_of_first_bit_set (unsigned mask)
{
  int bit;

  for (bit = 0;
       (mask & (1 << bit)) == 0;
       ++bit)
    continue;

  return bit;
}