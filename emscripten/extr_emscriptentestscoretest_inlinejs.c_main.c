#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double get () ; 
 int /*<<< orphan*/  printf (char*,double) ; 

int main() {
  asm("out('Inline JS is very cool')");
  printf("%.2f\n", get());

  // Test that passing multiple input and output variables works.
  int src1 = 1, src2 = 2, src3 = 3;
  int dst1 = 0, dst2 = 0, dst3 = 0;
  // TODO asm("out(%3); out(%4); out(%5); %0 = %3; %1
  // = %4; %2 = %5;" : "=r"(dst1),"=r"(dst2),"=r"(dst3):
  // "r"(src1),"r"(src2),"r"(src3));
  // TODO printf("%d\n%d\n%d\n", dst1, dst2, dst3);

  return 0;
}