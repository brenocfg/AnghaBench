#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int timezone; int time; scalar_t__ dstflag; } ;
typedef  TYPE_1__ timeb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ftime (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main() {
  timeb tb;
  tb.timezone = 1;
  printf("*%d\n", ftime(&tb));
  assert(tb.time > 10000);
  assert(tb.timezone == 0);
  assert(tb.dstflag == 0);
  return 0;
}