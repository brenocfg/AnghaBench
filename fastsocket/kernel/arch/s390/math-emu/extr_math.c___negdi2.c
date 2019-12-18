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

long long
__negdi2 (long long u)
{

  union lll {
    long long ll;
    long s[2];
  };

  union lll w,uu;

  uu.ll = u;

  w.s[1] = -uu.s[1];
  w.s[0] = -uu.s[0] - ((int) w.s[1] != 0);

  return w.ll;
}