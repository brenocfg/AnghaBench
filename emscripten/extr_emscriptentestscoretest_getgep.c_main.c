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
struct TYPE_2__ {int* y; int* z; } ;

/* Variables and functions */
 TYPE_1__ commonblock ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main() {
  for (int i = 0; i < 10; ++i) {
    commonblock.y[i] = 1;
    commonblock.z[i] = 2;
  }
  printf("*%d %d*\n", commonblock.y[0], commonblock.z[0]);
  return 0;
}