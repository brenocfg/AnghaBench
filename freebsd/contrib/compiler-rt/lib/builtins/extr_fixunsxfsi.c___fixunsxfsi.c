#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int su_int ;
struct TYPE_7__ {int high; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {int low; } ;
struct TYPE_10__ {TYPE_3__ s; } ;
struct TYPE_11__ {TYPE_2__ low; TYPE_4__ high; } ;
struct TYPE_12__ {long double f; TYPE_5__ u; } ;
typedef  TYPE_6__ long_double_bits ;

/* Variables and functions */
 int CHAR_BIT ; 

su_int __fixunsxfsi(long double a) {
  long_double_bits fb;
  fb.f = a;
  int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
  if (e < 0 || (fb.u.high.s.low & 0x00008000))
    return 0;
  if ((unsigned)e > sizeof(su_int) * CHAR_BIT)
    return ~(su_int)0;
  return fb.u.low.s.high >> (31 - e);
}