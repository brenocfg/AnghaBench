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
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  swab (char*,char*,int) ; 

int main() {
  char src[] = "abcdefg";
  char dst[10] = {0};
  swab(src, dst, 5);

  printf("before: %s\n", src);
  printf("after: %s\n", dst);

  return 0;
}