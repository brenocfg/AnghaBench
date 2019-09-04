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
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int volatile) ; 
 int /*<<< orphan*/  printf (char*,int volatile) ; 
 int setjmp (int /*<<< orphan*/ ) ; 

int main() {
  volatile int x = 0;
  printf("setjmp:%d\n", setjmp(buf));
  x++;
  printf("x:%d\n", x);
  if (x < 4) longjmp(buf, x * 2);
  return 0;
}