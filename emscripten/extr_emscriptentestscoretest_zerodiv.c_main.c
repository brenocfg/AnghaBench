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
 int /*<<< orphan*/  printCanonicalizedNan (char*,float) ; 

int main(int argc, const char* argv[]) {
  float f1 = 1.0f;
  float f2 = 0.0f;
  float f_zero = 0.0f;

  float f3 = 0.0f / f2;
  float f4 = f2 / 0.0f;
  float f5 = f2 / f2;
  float f6 = f2 / f_zero;

  printCanonicalizedNan("f3", f3);
  printCanonicalizedNan("f4", f4);
  printCanonicalizedNan("f5", f5);
  printCanonicalizedNan("f6", f6);

  return 0;
}