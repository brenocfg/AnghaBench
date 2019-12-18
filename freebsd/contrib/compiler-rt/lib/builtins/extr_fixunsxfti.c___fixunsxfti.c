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
struct TYPE_6__ {int all; } ;
struct TYPE_7__ {int low; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
struct TYPE_9__ {TYPE_1__ low; TYPE_3__ high; } ;
struct TYPE_10__ {long double f; TYPE_4__ u; } ;
typedef  TYPE_5__ long_double_bits ;

/* Variables and functions */
 int CHAR_BIT ; 

tu_int __fixunsxfti(long double a) {
  long_double_bits fb;
  fb.f = a;
  int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
  if (e < 0 || (fb.u.high.s.low & 0x00008000))
    return 0;
  if ((unsigned)e > sizeof(tu_int) * CHAR_BIT)
    return ~(tu_int)0;
  tu_int r = fb.u.low.all;
  if (e > 63)
    r <<= (e - 63);
  else
    r >>= (63 - e);
  return r;
}