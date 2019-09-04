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

__attribute__((used)) static int multiply(unsigned long *amount, long with)
{
  unsigned long sum = *amount * with;
  if(!with) {
    *amount = 0;
    return 0;
  }
  if(sum/with != *amount)
    return 1; /* didn't fit, bail out */
  *amount = sum;
  return 0;
}