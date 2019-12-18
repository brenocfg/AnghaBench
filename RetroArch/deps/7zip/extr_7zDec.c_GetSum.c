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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t GetSum(const uint64_t *values, uint32_t idx)
{
  uint64_t sum = 0;
  uint32_t i;
  for (i = 0; i < idx; i++)
    sum += values[i];
  return sum;
}