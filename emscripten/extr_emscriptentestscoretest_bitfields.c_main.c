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
struct TYPE_2__ {int x; int y; int z; } ;
typedef  TYPE_1__ bitty ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {
  bitty b;
  printf("*");
  for (int i = 0; i <= 1; i++)
    for (int j = 0; j <= 1; j++)
      for (int k = 0; k <= 1; k++) {
        b.x = i;
        b.y = j;
        b.z = k;
        printf("%d,%d,%d,", b.x, b.y, b.z);
      }
  printf("*\n");
  return 0;
}