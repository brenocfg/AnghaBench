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

__attribute__((used)) static void memswap(void* p0, void* p1, size_t s) {
  if (p0 == p1) { return; }
  for (size_t i = 0; i < s; i++) {
    char t = ((char*)p0)[i];
    ((char*)p0)[i] = ((char*)p1)[i];
    ((char*)p1)[i] = t;
  }
}