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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq (double,long long) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  assert(eq(0.0, 0));
  assert(eq(-0.0, 0));
  assert(eq(0.1, 0));
  assert(eq(-0.1, 0));
  assert(eq(0.6, 0));
  assert(eq(-0.6, 0));
  assert(eq(1.0, 1));
  assert(eq(-1.0, -1));
  assert(eq(1.1, 1));
  assert(eq(-1.1, -1));
  assert(eq(1.6, 1));
  assert(eq(-1.6, -1));
  assert(eq(4294967295.0, 4294967295LL));
  assert(eq(4294967295.5, 4294967295LL));
  assert(eq(4294967296.0, 4294967296LL));
  assert(eq(4294967296.5, 4294967296LL));
  assert(eq(14294967295.0, 14294967295LL));
  assert(eq(14294967295.5, 14294967295LL));
  assert(eq(14294967296.0, 14294967296LL));
  assert(eq(14294967296.5, 14294967296LL));
  assert(eq(-4294967295.0, -4294967295LL));
  assert(eq(-4294967295.5, -4294967295LL));
  assert(eq(-4294967296.0, -4294967296LL));
  assert(eq(-4294967296.5, -4294967296LL));
  assert(eq(-14294967295.0, -14294967295LL));
  assert(eq(-14294967295.5, -14294967295LL));
  assert(eq(-14294967296.0, -14294967296LL));
  assert(eq(-14294967296.5, -14294967296LL));

  assert(eq(4294967295.3, 4294967295LL));
  assert(eq(4294967296.3, 4294967296LL));
  assert(eq(14294967295.3, 14294967295LL));
  assert(eq(14294967296.3, 14294967296LL));
  assert(eq(-4294967295.3, -4294967295LL));
  assert(eq(-4294967296.3, -4294967296LL));
  assert(eq(-14294967295.3, -14294967295LL));
  assert(eq(-14294967296.3, -14294967296LL));

  assert(eq(4294967295.8, 4294967295LL));
  assert(eq(4294967296.8, 4294967296LL));
  assert(eq(14294967295.8, 14294967295LL));
  assert(eq(14294967296.8, 14294967296LL));
  assert(eq(-4294967295.8, -4294967295LL));
  assert(eq(-4294967296.8, -4294967296LL));
  assert(eq(-14294967295.8, -14294967295LL));
  assert(eq(-14294967296.8, -14294967296LL));

  // The following number is the largest double such that all integers smaller
  // than this can exactly be represented in a double.
  assert(eq(9007199254740992.0, 9007199254740992LL /* == 2^53 */));
  assert(eq(-9007199254740992.0, -9007199254740992LL /* == -2^53 */));

  printf("OK!\n");
  return 0;
}