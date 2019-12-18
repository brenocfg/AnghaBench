#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int low; int high; } ;
struct TYPE_4__ {void* all; TYPE_1__ s; } ;
typedef  TYPE_2__ twords ;
typedef  void* ti_int ;

/* Variables and functions */
 void* __mulddi3 (int,int) ; 

ti_int __multi3(ti_int a, ti_int b) {
  twords x;
  x.all = a;
  twords y;
  y.all = b;
  twords r;
  r.all = __mulddi3(x.s.low, y.s.low);
  r.s.high += x.s.high * y.s.low + x.s.low * y.s.high;
  return r.all;
}