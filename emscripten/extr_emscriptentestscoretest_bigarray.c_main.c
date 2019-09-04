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
struct TYPE_2__ {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* buffy ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main() {
  for (int i = 0; i < SIZE; i++) {
    assert(buffy[i].x == 0 && buffy[i].y == 0);
  }  // we were zeroinitialized
  for (int i = 0; i < SIZE; i++) {
    buffy[i].x = i * i;
    buffy[i].y = i * i * i;
  }  // we can save data
  printf("*%d*\n", buffy[SIZE / 3].x);
  return 0;
}