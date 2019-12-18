#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int si_int ;
struct TYPE_8__ {int all; } ;
struct TYPE_6__ {int low; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_3__ low; TYPE_2__ high; } ;
struct TYPE_10__ {long double f; TYPE_4__ u; } ;
typedef  TYPE_5__ long_double_bits ;
typedef  int du_int ;
typedef  int di_int ;

/* Variables and functions */
 int CHAR_BIT ; 

di_int __fixxfdi(long double a) {
  const di_int di_max = (di_int)((~(du_int)0) / 2);
  const di_int di_min = -di_max - 1;
  long_double_bits fb;
  fb.f = a;
  int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
  if (e < 0)
    return 0;
  if ((unsigned)e >= sizeof(di_int) * CHAR_BIT)
    return a > 0 ? di_max : di_min;
  di_int s = -(si_int)((fb.u.high.s.low & 0x00008000) >> 15);
  di_int r = fb.u.low.all;
  r = (du_int)r >> (63 - e);
  return (r ^ s) - s;
}