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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int sscanf (char*,char*,int*,...) ; 

int main() {
  int val1;
  printf("%d\n", sscanf("10 20 30 40", "%*lld %*d %d", &val1));
  printf("%d\n", val1);

  int64_t large, val2;
  printf("%d\n", sscanf("1000000 -1125899906842620 -123 -1073741823",
                        "%lld %*lld %lld %*d", &large, &val2));
  printf("%lld,%lld\n", large, val2);

  return 0;
}