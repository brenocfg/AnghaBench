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

int countPrefixOnes(char c) {
  unsigned char mask = 127;
  mask = ~mask;
  int ret = 0;
  while ((c & mask) != 0) {
    ret++;
    c <<= 1;
  }

  return ret;
}