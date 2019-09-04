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
 int atoi (char*) ; 
 scalar_t__ atol (char*) ; 
 int atoll (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main() {
  printf("%d*", atoi(""));
  printf("%d*", atoi("a"));
  printf("%d*", atoi(" b"));
  printf("%d*", atoi(" c "));
  printf("%d*", atoi("6"));
  printf("%d*", atoi(" 5"));
  printf("%d*", atoi("4 "));
  printf("%d*", atoi("3 6"));
  printf("%d*", atoi(" 3 7"));
  printf("%d*", atoi("9 d"));
  printf("%d\n", atoi(" 8 e"));
  printf("%d*", (int)atol(""));
  printf("%d*", (int)atol("a"));
  printf("%d*", (int)atol(" b"));
  printf("%d*", (int)atol(" c "));
  printf("%d*", (int)atol("6"));
  printf("%d*", (int)atol(" 5"));
  printf("%d*", (int)atol("4 "));
  printf("%d*", (int)atol("3 6"));
  printf("%d*", (int)atol(" 3 7"));
  printf("%d*", (int)atol("9 d"));
  printf("%d\n", (int)atol(" 8 e"));
  printf("%lld*", atoll("6294967296"));
  printf("%lld*", atoll(""));
  printf("%lld*", atoll("a"));
  printf("%lld*", atoll(" b"));
  printf("%lld*", atoll(" c "));
  printf("%lld*", atoll("6"));
  printf("%lld*", atoll(" 5"));
  printf("%lld*", atoll("4 "));
  printf("%lld*", atoll("3 6"));
  printf("%lld*", atoll(" 3 7"));
  printf("%lld*", atoll("9 d"));
  printf("%lld\n", atoll(" 8 e"));
  return 0;
}