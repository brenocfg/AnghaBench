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
 int /*<<< orphan*/  printf (char*,int) ; 

int main(int argc, char* argv[]) {
  int one = argc;

  printf("%d ", 0 * one);
  printf("%d ", 0 * -one);
  printf("%d ", -one * 0);
  printf("%g ", 0.0 * one);
  printf("%g ", 0.0 * -one);
  printf("%g", -one * 0.0);
  return 0;
}