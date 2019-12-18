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
typedef  int tu_int ;
typedef  int ti_int ;
typedef  int si_int ;
struct TYPE_8__ {int all; } ;
struct TYPE_6__ {int low; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_3__ low; TYPE_2__ high; } ;
struct TYPE_10__ {long double f; TYPE_4__ u; } ;
typedef  TYPE_5__ long_double_bits ;

/* Variables and functions */
 int CHAR_BIT ; 

ti_int __fixxfti(long double a) {
  const ti_int ti_max = (ti_int)((~(tu_int)0) / 2);
  const ti_int ti_min = -ti_max - 1;
  long_double_bits fb;
  fb.f = a;
  int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
  if (e < 0)
    return 0;
  ti_int s = -(si_int)((fb.u.high.s.low & 0x00008000) >> 15);
  ti_int r = fb.u.low.all;
  if ((unsigned)e >= sizeof(ti_int) * CHAR_BIT)
    return a > 0 ? ti_max : ti_min;
  if (e > 63)
    r <<= (e - 63);
  else
    r >>= (63 - e);
  return (r ^ s) - s;
}