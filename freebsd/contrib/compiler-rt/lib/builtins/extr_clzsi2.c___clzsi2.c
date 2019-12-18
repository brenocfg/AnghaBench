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
typedef  int su_int ;
typedef  int si_int ;

/* Variables and functions */

si_int __clzsi2(si_int a) {
  su_int x = (su_int)a;
  si_int t = ((x & 0xFFFF0000) == 0) << 4; // if (x is small) t = 16 else 0
  x >>= 16 - t;                            // x = [0 - 0xFFFF]
  su_int r = t;                            // r = [0, 16]
  // return r + clz(x)
  t = ((x & 0xFF00) == 0) << 3;
  x >>= 8 - t; // x = [0 - 0xFF]
  r += t;      // r = [0, 8, 16, 24]
  // return r + clz(x)
  t = ((x & 0xF0) == 0) << 2;
  x >>= 4 - t; // x = [0 - 0xF]
  r += t;      // r = [0, 4, 8, 12, 16, 20, 24, 28]
  // return r + clz(x)
  t = ((x & 0xC) == 0) << 1;
  x >>= 2 - t; // x = [0 - 3]
  r += t;      // r = [0 - 30] and is even
  // return r + clz(x)
  //     switch (x)
  //     {
  //     case 0:
  //         return r + 2;
  //     case 1:
  //         return r + 1;
  //     case 2:
  //     case 3:
  //         return r;
  //     }
  return r + ((2 - x) & -((x & 2) == 0));
}