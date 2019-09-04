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
 int /*<<< orphan*/  isnan (float) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

void printCanonicalizedNan(char* name, float value) {
  if (!isnan(value)) {
    printf("%s: %f\n", name, value);
  } else {
    printf("%s: nan\n", name);
  }
}