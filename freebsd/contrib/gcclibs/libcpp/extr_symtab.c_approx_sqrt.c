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
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static double
approx_sqrt (double x)
{
  double s, d;

  if (x < 0)
    abort ();
  if (x == 0)
    return 0;

  s = x;
  do
    {
      d = (s * s - x) / (2 * s);
      s -= d;
    }
  while (d > .0001);
  return s;
}