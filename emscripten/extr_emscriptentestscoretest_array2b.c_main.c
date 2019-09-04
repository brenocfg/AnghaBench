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
struct TYPE_2__ {int left; int right; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 
 TYPE_1__* prioritah ; 

int main() {
  printf("*%d,%d\n", prioritah[1].left, prioritah[1].right);
  printf("%d,%d*\n", prioritah[2].left, prioritah[2].right);
  return 0;
}