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
typedef  int /*<<< orphan*/  si_int ;
struct TYPE_3__ {int high; int low; } ;
struct TYPE_4__ {TYPE_1__ s; int /*<<< orphan*/  all; } ;
typedef  TYPE_2__ dwords ;
typedef  int /*<<< orphan*/  di_int ;

/* Variables and functions */
 int /*<<< orphan*/  __paritysi2 (int) ; 

si_int __paritydi2(di_int a) {
  dwords x;
  x.all = a;
  return __paritysi2(x.s.high ^ x.s.low);
}