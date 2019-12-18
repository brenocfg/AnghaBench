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
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static HOST_WIDE_INT
int_log2 (HOST_WIDE_INT power)
{
  HOST_WIDE_INT shift = 0;

  while ((((HOST_WIDE_INT) 1 << shift) & power) == 0)
    {
      gcc_assert (shift <= 31);
      shift++;
    }

  return shift;
}