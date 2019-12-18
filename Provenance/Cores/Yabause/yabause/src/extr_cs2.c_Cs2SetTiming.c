#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int speed1x; int _periodictiming; scalar_t__ isaudio; } ;

/* Variables and functions */
 TYPE_1__* Cs2Area ; 

void Cs2SetTiming(int playing) {
  if (playing) {
     if (Cs2Area->isaudio || Cs2Area->speed1x == 1)
        Cs2Area->_periodictiming = 40000;  // 13333.333... * 3
     else
        Cs2Area->_periodictiming = 20000;  // 6666.666... * 3
  }
  else {
     Cs2Area->_periodictiming = 50000;  // 16666.666... * 3
  }
}